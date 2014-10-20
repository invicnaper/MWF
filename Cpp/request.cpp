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

#include "cppw_request.h"

#include "cppw_ipc.h"
#include "cppw_const.h"
#include "cppw_ccgi.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

string GetEnv(const char* cName)
{
    char* var = getenv(cName);
    if(var == NULL)
        return "";
    return var;
}

CWRequest::CWRequest()
{
    Query = new CWStringList();
    Post = new CWStringList();
    Cookie = new CWStringList();
    Env = new CWStringList();
}

CWRequest::~CWRequest()
{
    delete Env;
    delete Cookie;
    delete Post;
    delete Query;
}

void CWRequest::Clear()
{
    Query->Clear();
    Post->Clear();
    Cookie->Clear();
    Env->Clear();
}

bool CWRequest::IsDynamic()
{
    return GetValue("load_dynamic") == "true" || GetValue("load_dynamic") == "1";
}

string CWRequest::GetServerURL(bool bRelative)
{
    if(bRelative)
        return "";

    string link = "";
    int server_port = StrToIntDef(Env->GetValue("SERVER_PORT"), -1);

    if(Env->GetValue("HTTPS") == "on")
    {
        link.append("https://");
        link.append(Env->GetValue("SERVER_NAME"));

        if(server_port > 0 && server_port != 443)
            link.append(":" + IntToStr(server_port));
    }
    else
    {
        link.append("http://");
        link.append(Env->GetValue("SERVER_NAME"));
        if(server_port > 0 && server_port != 80)
            link.append(":" + IntToStr(server_port));
    }

    return link;
}

string CWRequest::GetScriptURL(bool bRelative)
{
    if(bRelative)
        return Env->GetValue("SCRIPT_NAME");

    string link = "";
    int server_port = StrToIntDef(Env->GetValue("SERVER_PORT"), -1);

    if(Env->GetValue("HTTPS") == "on")
    {
        link.append("https://");
        link.append(Env->GetValue("SERVER_NAME"));

        if(server_port > 0 && server_port != 443)
            link.append(":" + IntToStr(server_port));
    }
    else
    {
        link.append("http://");
        link.append(Env->GetValue("SERVER_NAME"));
        if(server_port > 0 && server_port != 80)
            link.append(":" + IntToStr(server_port));
    }

    link.append(Env->GetValue("SCRIPT_NAME"));

    return link;
}

string CWRequest::GetURL(CWStringList* Params, bool bRelative, bool bURLEncode)
{
    string link = GetScriptURL(bRelative);
    if(Params != NULL)
    {
        int param_count = Params->Count();
        for(int i = 0; i < param_count; i++)
        {
            if(i == 0)
                link = link + "?";
            else
            {
                if(bURLEncode)
                    link = link + "&amp;";
                else
                    link = link + "&";
            }

            string param = Params->Strings[i];
            if(param.find('=') == string::npos)
            {
                if(bURLEncode)
                    link = link + URLEncode(param);
                else
                    link = link + param;
            }
            else
            {
                if(bURLEncode)
                    link = link + URLEncode(Params->GetName(i)) + "=" + URLEncode(Params->GetValue(i));
                else
                    link = link + Params->GetName(i) + "=" + Params->GetValue(i);
            }
        }
    }
    return link;
}

string CWRequest::GetURL(string sParams, bool bRelative, bool bURLEncode)
{
    if(sParams == "")
        return GetURL(NULL, bRelative, bURLEncode);
    CWStringList params;
    params.SetText(sParams);
    return GetURL(&params, bRelative, bURLEncode);
}

int CWRequest::FindCookie(string sName)
{
    return Cookie->FindName(sName);
}

string CWRequest::GetCookie(string sName)
{
    return Cookie->GetValue(sName);
}

void CWRequest::GetCookies(string sName, CWStringList* pValues)
{
    pValues->Clear();
    Cookie->GetValues(sName, pValues);
}

int CWRequest::FindValue(string sName)
{
    int res = -1;

    res = Query->FindName(sName);
    if(res >= 0) return res;

    res = Post->FindName(sName);
    if(res >= 0) return res;

    res = Cookie->FindName(sName);
    if(res >= 0) return res;

    res = Env->FindName(sName);
    if(res >= 0) return res;

    return -1;
}

string CWRequest::GetValue(string sName)
{
    int pos = -1;

    if((pos = Query->FindName(sName)) >= 0)
        return Query->GetValue(pos);

    if((pos = Post->FindName(sName)) >= 0)
        return Post->GetValue(pos);

    if((pos = Cookie->FindName(sName)) >= 0)
        return Cookie->GetValue(pos);

    if((pos = Env->FindName(sName)) >= 0)
        return Env->GetValue(pos);

    return "";
}

void CWRequest::GetValues(string sName, CWStringList* pValues)
{
    pValues->Clear();

    CWStringList values;

    Query->GetValues(sName, &values);
    pValues->Append(&values);

    Post->GetValues(sName, &values);
    pValues->Append(&values);

    Cookie->GetValues(sName, &values);
    pValues->Append(&values);

    Env->GetValues(sName, &values);
    pValues->Append(&values);
}

void CWRequest::DeleteNameValue(string sName)
{
    Query->DeleteNameValue(sName);
    Post->DeleteNameValue(sName);
    Cookie->DeleteNameValue(sName);
    Env->DeleteNameValue(sName);
}

string CWRequest::CreateSessionID()
{
    return CreateID("session_id");
}

string CWRequest::CreateRequestID()
{
    return CreateID("request_id");
}

bool CWRequest::ReceiveFromWeb(string* pSessionID, string* pRequestID, bool* pThisIsCookieCheck, bool* pCookieCheckOk, bool* pLongPolling, bool* pKeepAlive, string* pErrorMessage)
{
    Clear();

    CGI_varlist* query = 0;
    CGI_varlist* post = 0;
    CGI_varlist* cookie = 0;

    string file_upload_template = TempDir() + "cgi-upload-XXXXXX";

    query = CGI_get_query(NULL);
    post = CGI_get_post(NULL, file_upload_template.c_str());
    cookie = CGI_get_cookie(NULL);

    if(query != 0)
    {
        const char *name = 0;
        CGI_value  *value = 0;
        for(name = CGI_first_name(query); name != 0; name = CGI_next_name(query))
        {
            value = CGI_lookup_all(query, 0);
            for(int i = 0; value[i] != 0; i++)
            {
                string name_value = "";
                name_value = name_value + name;
                name_value = name_value + "=";
                name_value = name_value + value[i];
                Query->Add(name_value);
            }
        }
    }

    if(post != 0)
    {
        const char *name = 0;
        CGI_value  *value = 0;
        for(name = CGI_first_name(post); name != 0; name = CGI_next_name(post))
        {
            value = CGI_lookup_all(post, 0);
            for(int i = 0; value[i] != 0; i++)
            {
                string name_value = "";
                name_value = name_value + name;
                name_value = name_value + "=";
                name_value = name_value + value[i];
                Post->Add(name_value);
            }
        }
    }

    if(cookie != 0)
    {
        const char *name = 0;
        CGI_value  *value = 0;
        for(name = CGI_first_name(cookie); name != 0; name = CGI_next_name(cookie))
        {
            value = CGI_lookup_all(cookie, 0);
            for(int i = 0; value[i] != 0; i++)
            {
                string name_value = "";
                name_value = name_value + name;
                name_value = name_value + "=";
                name_value = name_value + value[i];
                Cookie->Add(name_value);
            }
        }
    }

    CGI_free_varlist(cookie);
    CGI_free_varlist(post);
    CGI_free_varlist(query);

    // environment variables
    Env->SetValue("SERVER_NAME", GetEnv("SERVER_NAME"));
    Env->SetValue("SERVER_PORT", GetEnv("SERVER_PORT"));
    Env->SetValue("SCRIPT_NAME", GetEnv("SCRIPT_NAME"));
    Env->SetValue("REQUEST_METHOD", GetEnv("REQUEST_METHOD"));
    Env->SetValue("DOCUMENT_ROOT", GetEnv("DOCUMENT_ROOT"));
    Env->SetValue("REMOTE_ADDR", GetEnv("REMOTE_ADDR"));
    Env->SetValue("HTTP_USER_AGENT", GetEnv("HTTP_USER_AGENT"));
    Env->SetValue("HTTP_REFERER", GetEnv("HTTP_REFERER"));
    Env->SetValue("HTTP_COOKIE", GetEnv("HTTP_COOKIE"));
    Env->SetValue("CONTENT_TYPE", GetEnv("CONTENT_TYPE"));
    Env->SetValue("HTTPS", GetEnv("HTTPS"));

    // read and return session_id
    string session_id = Cookie->GetValue("session_id");
    string request_id = CreateRequestID();
    bool this_is_cookie_check = GetValue("cookie_check") == "1" || GetValue("cookie_check") == "true";
    DeleteNameValue("cookie_check");
    bool cookie_check_ok = Cookie->GetValue("cookie_check_data") == "123";
    bool long_polling = GetValue("long_polling") == "1" || GetValue("long_polling") == "true";
    bool keep_alive = GetValue("keep_alive") == "1" || GetValue("keep_alive") == "true";

    if(pSessionID != NULL) *pSessionID = session_id;
    if(pRequestID != NULL) *pRequestID = request_id;
    if(pThisIsCookieCheck != NULL) *pThisIsCookieCheck = this_is_cookie_check;
    if(pCookieCheckOk != NULL) *pCookieCheckOk = cookie_check_ok;
    if(pLongPolling != NULL) *pLongPolling = long_polling;
    if(pKeepAlive != NULL) *pKeepAlive = keep_alive;

    return true;
}

bool CWRequest::IsServerRunning(string sSessionID, int iTimeoutMS, string* pErrorMessage)
{
    if(sSessionID == "")
    {
        if(pErrorMessage != NULL) *pErrorMessage = "Session ID is empty.";
        return false;
    }

    // read server pid
    string instance_filename = TempDir() + sSessionID + ".server";
    int fd = -1;
    int file_size = 0;
    if(!FileOpenExistingAndLock(instance_filename, iTimeoutMS, &fd, &file_size, pErrorMessage))
        return false;

    int server_pid = 0;
    if(!FileReadInt(fd, &server_pid, pErrorMessage))
    {
        FileUnlockAndClose(fd, NULL);
        return false;
    }
    FileUnlockAndClose(fd, NULL);

    // check if server is running
    if(!IsProcessRunning(server_pid))
    {
        if(pErrorMessage != NULL) *pErrorMessage = "Server is not running.";

        // if server is not running, delete server pid file and server queue
        FileDelete(instance_filename, NULL);

        string queue_filename = TempDir() + sSessionID + ".queue";
        if(FileExists(queue_filename))
            FileDelete(queue_filename, NULL);

        return false;
    }

    return true;
}

bool CWRequest::StartServer(string sServerPath, int iTimeoutMS, string* pSessionID, string* pErrorMessage)
{
    if(sServerPath == "")
    {
        if(pErrorMessage != NULL) *pErrorMessage = "Server application not specified.";
        return false;
    }

    if(!FileExists(sServerPath))
    {
        if(pErrorMessage != NULL) *pErrorMessage = "Server application not found.";
        return false;
    }

    // create session ID
    string session_id = CreateSessionID();

    // start server
    string args = "-s " + session_id;
    if(!Execute(sServerPath, args, 0, pErrorMessage))
        return false;

    if(!IsServerRunning(session_id, iTimeoutMS, pErrorMessage))
        return false;

    *pSessionID = session_id;
    return true;
}

bool CWRequest::SendToServer(string sServerPath, string* pSessionID, string sRequestID, bool bLongPolling, bool bKeepAlive, string* pErrorMessage)
{
    string session_id = *pSessionID;

    if(session_id == "" || !IsServerRunning(session_id, INSTANCE_CHECK_TIMEOUT, pErrorMessage))
    {
        if(bLongPolling || bKeepAlive)
            return false;

        if(!StartServer(sServerPath, INSTANCE_START_TIMEOUT, &session_id, pErrorMessage))
            return false;
    }

    // ---
    // write request to file
    // ---
    string request_filename = TempDir() + sRequestID + ".request";

    int fd = -1;
    if(!FileCreateNonExistingAndLock(request_filename, REQUEST_WRITE_TIMEOUT, &fd, pErrorMessage))
        return false;

    // query
    if(!FileWriteStringList(fd, Query, pErrorMessage))
    {
        FileUnlockAndClose(fd, NULL);
        return false;
    }

    // post
    if(!FileWriteStringList(fd, Post, pErrorMessage))
    {
        FileUnlockAndClose(fd, NULL);
        return false;
    }

    // cookie
    if(!FileWriteStringList(fd, Cookie, pErrorMessage))
    {
        FileUnlockAndClose(fd, NULL);
        return false;
    }

    // env
    if(!FileWriteStringList(fd, Env, pErrorMessage))
    {
        FileUnlockAndClose(fd, NULL);
        return false;
    }

    FileUnlockAndClose(fd, NULL);

    // request type
    string queue_filename = "";
    if(bLongPolling)
        queue_filename = TempDir() + session_id + ".queue_lp";
    else
        queue_filename = TempDir() + session_id + ".queue";

    // ---
    // register request in queue
    // ---
    if(!PushData(queue_filename, (char*)sRequestID.c_str(), sRequestID.size(), REQUEST_SEND_TIMEOUT, pErrorMessage))
        return false;

    *pSessionID = session_id;

    Clear();

    return true;
}

bool CWRequest::ReceiveFromBridge(string sSessionID, string* pRequestID, bool* pSetResponseCookie, bool* pSecure, bool* pKeepAlive, bool bLongPolling, int iTimeoutMS, CWCallbackFunction pCallback, const void* pCallbackArg, int iCallbackIntervalMS, string* pErrorMessage)
{
    if(sSessionID == "")
    {
        if(pErrorMessage != NULL) *pErrorMessage = "session_id is empty.";
        return false;
    }

    Clear();

    // ---
    // read request id from queue
    // ---
    string queue_filename = "";
    if(bLongPolling)
    {
        queue_filename = TempDir() + sSessionID + ".queue_lp";

        // if no long polling request is waiting, return false
        int queue_size = 0;
        if(!FileExists(queue_filename, &queue_size))
            return false;

        if(queue_size <= 0)
            return false;
    }
    else
        queue_filename = TempDir() + sSessionID + ".queue";

    char* buffer = NULL;
    int buffer_size = 0;
    if(!PopData(queue_filename, (void**)&buffer, &buffer_size, iTimeoutMS, pCallback, pCallbackArg, iCallbackIntervalMS, pErrorMessage))
        return false;

    string request_id(buffer, buffer_size);
    free(buffer);

    // ---
    // read request from file
    // ---
    string request_filename = TempDir() + request_id + ".request";

    int fd = -1;
    int file_size = 0;
    if(!FileOpenExistingAndLock(request_filename, REQUEST_RECEIVE_TIMEOUT, &fd, &file_size, pErrorMessage))
        return false;

    // query
    if(!FileReadStringList(fd, Query, pErrorMessage))
    {
        FileUnlockAndClose(fd, NULL);
        return false;
    }

    // post
    if(!FileReadStringList(fd, Post, pErrorMessage))
    {
        FileUnlockAndClose(fd, NULL);
        return false;
    }

    // cookie
    if(!FileReadStringList(fd, Cookie, pErrorMessage))
    {
        FileUnlockAndClose(fd, NULL);
        return false;
    }

    // env
    if(!FileReadStringList(fd, Env, pErrorMessage))
    {
        FileUnlockAndClose(fd, NULL);
        return false;
    }

    // unlock file
    FileUnlockAndClose(fd, NULL);

    // delete file
    FileDelete(request_filename, NULL);

    if(Cookie->GetValue("session_id") != sSessionID)
    {
        Cookie->SetValue("session_id", sSessionID);
        *pSetResponseCookie = true;
    }
    else
        *pSetResponseCookie = false;

    if(Env->GetValue("HTTPS") == "on")
        *pSecure = true;
    else
        *pSecure = false;

    if(pKeepAlive != NULL) *pKeepAlive = GetValue("keep_alive") == "1" || GetValue("keep_alive") == "true";

    *pRequestID = request_id;

    return true;
}
