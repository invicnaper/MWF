///////////////////////////////////////////////////////////////////////////////
//                                                                             
//  Copyright (C) 2008-2012  Artyom Beilis (Tonkikh) <artyomtnk@yahoo.com>     
//                                                                             
//  See accompanying file COPYING.TXT file for licensing details.
//
///////////////////////////////////////////////////////////////////////////////
#define CPPCMS_SOURCE
#include <cppcms/util.h>
#include "http_protocol.h"
#include <stdio.h>
#include <iterator>
#include "md5.h"
#include "tohex.h"

namespace cppcms {
namespace util {

std::string escape(std::string const &s)
{
	std::string content;
	unsigned i,len=s.size();
	content.reserve(len*3/2);
	for(i=0;i<len;i++) {
		char c=s[i];
		switch(c){
			case '<': content+="&lt;"; break;
			case '>': content+="&gt;"; break;
			case '&': content+="&amp;"; break;
			case '\"': content+="&quot;"; break;
			default: content+=c;
		}
	}
	return content;
}


void escape(char const *begin,char const *end,std::ostream &output)
{
	while(begin!=end) {
		char c=*begin++;
		switch(c){
			case '<': output << "&lt;"; break;
			case '>': output << "&gt;"; break;
			case '&': output << "&amp;"; break;
			case '\"': output<<"&quot;"; break;
			default: output << c;
		}
	}
}

template<typename Iterator>
void urlencode_impl(char const *b,char const *e,Iterator out)
{
	while(b!=e){
		char c=*b++;
		if(	('a'<=c && c<='z')
			|| ('A'<=c && c<='Z')
			|| ('0'<=c && c<='9'))
		{
			*out++ = c;
		}
		else {
			switch(c) {
				case '-':
				case '_':
				case '.':
				case '~':
					*out++ = c;
					break;
				default:
				{
					static char const hex[]="0123456789abcdef";
					unsigned char uc = c;
					*out++ = '%';
					*out++ = hex[(uc >> 4) & 0xF];
					*out++ = hex[ uc & 0xF];
					
				}
			};
		}
	};
}

void urlencode(char const *b,char const *e,std::ostream &out)
{
	std::ostream_iterator<char> it(out);
	urlencode_impl(b,e,it);
}
std::string urlencode(std::string const &s)
{
	std::string content;
	content.reserve(3*s.size());
	std::back_insert_iterator<std::string> out(content);
	urlencode_impl(s.c_str(),s.c_str()+s.size(),out);
	return content;
}


std::string urldecode(std::string const &s)
{
	return urldecode(s.c_str(),s.c_str()+s.size());
}
// TODO: Find correct RFC for proprer decoding
std::string urldecode(char const *begin,char const *end)
{
	std::string result;
	result.reserve(end-begin);
	for(;begin<end;begin++) {
		char c=*begin;
		switch(c) {
		case '+': result+=' ';
			break;
		case '%':
			if(end-begin >= 3 && http::protocol::xdigit(begin[1]) && http::protocol::xdigit(begin[2])) {
				char buf[3]={begin[1],begin[2],0};
				int value;
				sscanf(buf,"%x",&value);
				result+=char(value);
				begin+=2;
			}
			break;
		default:
			result+=c;
		
		}
	}
	return result;
}

std::string md5(std::string const &in)
{
	using namespace cppcms::impl;
	unsigned char data[16];
	md5_state_t state;
	md5_init(&state);
	md5_append(&state,reinterpret_cast<unsigned const char *>(in.c_str()),in.size());
	md5_finish(&state,data);
	return std::string(reinterpret_cast<char *>(data),16);
}

std::string md5hex(std::string const &in)
{
	using namespace cppcms::impl;
	unsigned char data[16];
	md5_state_t state;
	md5_init(&state);
	md5_append(&state,reinterpret_cast<unsigned const char *>(in.c_str()),in.size());
	md5_finish(&state,data);
	char buf[33]={0};
	impl::tohex(data,sizeof(data),buf);
	return buf;
}



} // util
} // util
