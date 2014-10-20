#include "cppw_mail.h"

#include "cppw_file.h"
#include "cppw_process.h"

#ifdef _WIN32
	#define DEFAULT_SENDMAIL_PATH "sendmail.exe"
#else
	#define DEFAULT_SENDMAIL_PATH "/usr/lib/sendmail"
#endif

bool SendMail(string sFrom, string sTo, string sSubject, string sBody, bool bIsHTML, string sSendMailPath, string* pErrorMessage)
{
    string message = "";

    if(sFrom != "") message.append("From: " + sFrom + "\r\n");
    if(sTo != "") message.append("To: " + sTo + "\r\n");
    if(sSubject != "") message.append("Subject: " + sSubject + "\r\n");
    if(bIsHTML)
        message.append("Content-Type: text/html\r\n");
    else
        message.append("Content-Type: text/plain\r\n");

    if(sBody != "") message.append(sBody);

    string temp_file_name = TempDir() + CreateID(sFrom + sTo) + ".tmp";
    if(!FileSaveString(temp_file_name, message, 0, pErrorMessage))
        return false;

	string sendmail_path = "";
	if(sSendMailPath == "")
		sendmail_path = DEFAULT_SENDMAIL_PATH;
	else
		sendmail_path = sSendMailPath;

    string arguments = "";
    arguments.append("-t < ");
    arguments.append("\"" + temp_file_name + "\"");
    if(!Execute(sendmail_path, arguments, true, pErrorMessage))
    {
        FileDelete(temp_file_name, NULL);
        return false;
    }

    FileDelete(temp_file_name, NULL);

    return true;
}
