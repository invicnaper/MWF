/*
Copyright (c) 2013 Petar Korponaić

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "cppw_server.h"

#include "cppw_process.h"
#include "cppw_const.h"
#include "cppw_file.h"

CWServer::CWServer(int argc, char* argv[]): CWProgram(argc, argv)
{
    SessionID = "";
    for(int i = 0; i < argc; i++)
    {
        string argument = argv[i];
        // -s <session_id>
        if(argument == "-s" && i < argc - 1)
            SessionID = argv[i + 1];
    }
    // ---

    RequestID = "";
    SetResponseCookie = false;
    Secure = false;
    KeepAlive = false;

    SessionTimeoutMS = SESSION_TIMEOUT;
    CallbackIntervalMS = CALLBACK_INTERVAL;

    string msg = "";
    RegisterInstance(&msg);
}

CWServer::~CWServer()
{
    string msg = "";
    UnregisterInstance(&msg);
}

bool CWServer::RegisterInstance(string* pErrorMessage)
{
    if(SessionID == "")
    {
        if(pErrorMessage != NULL) *pErrorMessage = "Session ID is empty.";
        return false;
    }

    int pid = GetProcessID();
    string instance_filename = TempDir() + SessionID + ".server";
    if(!FileSave(instance_filename, (void*)&pid, sizeof(int), INSTANCE_REGISTER_TIMEOUT, pErrorMessage))
        return false;

    return true;
}

bool CWServer::UnregisterInstance(string* pErrorMessage)
{
    if(SessionID == "")
    {
        if(pErrorMessage != NULL) *pErrorMessage = "Session ID is empty.";
        return false;
    }

    string instance_filename = TempDir() + SessionID + ".server";
    if(FileExists(instance_filename))
        FileDelete(instance_filename, NULL);

    string queue_filename = TempDir() + SessionID + ".queue";
    if(FileExists(queue_filename))
        FileDelete(queue_filename, NULL);

    return true;
}

bool CWServer::ReceiveRequest(string* pErrorMessage)
{
    if(!Request->ReceiveFromBridge(SessionID, &RequestID, &SetResponseCookie, &Secure, &KeepAlive, false, SessionTimeoutMS, Callback, this, CallbackIntervalMS, pErrorMessage))
        return false;

    return true;
}

bool CWServer::SendResponse(string* pErrorMessage)
{
    if(!Response->SendToBridge(SessionID, RequestID, SetResponseCookie, Secure, pErrorMessage))
        return false;

    return true;
}

bool CWServer::PushResponse(string* pErrorMessage)
{
    CWRequest* lp_request = new CWRequest();
    string request_id = "";
    bool set_response_cookie = false;
    bool secure = false;
    bool keep_alive = false;
    bool copy_temp_files = Response->ContentSource == csTempFile && Response->FileName != "";

    while(lp_request->ReceiveFromBridge(SessionID, &request_id, &set_response_cookie, &secure, &keep_alive, true, REQUEST_RECEIVE_TIMEOUT, Callback, this, CallbackIntervalMS, NULL))
    {
        CWResponse* lp_response = new CWResponse();
        lp_response->Assign(Response);
        if(copy_temp_files)
        {
            lp_response->FileName = TempDir() + CreateID("temp_file") + ".temp";
            FileCopy(Response->FileName, lp_response->FileName, true, 0, NULL);
        }
        lp_response->SendToBridge(SessionID, request_id, false, secure, NULL);
        delete lp_response;
    }
    if(copy_temp_files)
        FileDelete(Response->FileName, NULL);
    Response->Clear();

    delete lp_request;
    return true;
}

bool CWServer::Run(string* pErrorMessage)
{
    // load config
    if(!LoadConfig(pErrorMessage))
        return false;

    if(!LoadTemplate(pErrorMessage))
        return false;

    bool first_request = true;

    // main loop
    for(;;)
    {
        if(!ReceiveRequest(pErrorMessage))
            return false;

        if(KeepAlive)
        {
            Response->Clear();
            Response->Method = rmData;
            Response->ContentType = "application/json";
            Response->ContentSource = csText;
            Response->Text = "{}";
        }
        else
        {
            if(first_request)
            {
                first_request = false;
                if(!OnInit(pErrorMessage))
                    return false;
            }

            if(!OnRequest(pErrorMessage))
                return false;
        }

        if(!SendResponse(pErrorMessage))
            return false;
    }
    return true;
}

bool CWServer::Callback(const void* pCWServer, string* pErrorMessage)
{
    if(pCWServer != NULL)
    {
        CWServer* server = (CWServer*)pCWServer;
        return server->OnCallback(pErrorMessage);
    }
    return true;
}

bool CWServer::OnRequest(string* pErrorMessage)
{
    if(!CWProgram::OnRequest(pErrorMessage))
        return false;

    return true;
}

bool CWServer::OnCallback(string* pErrorMessage)
{
    if(!CWProgram::OnCallback(pErrorMessage))
        return false;

    return true;
}
