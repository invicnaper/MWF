=begin
 _   _  _ _ _  ___ 
| \_/ || | | || __|
| \_/ || V V || _| 
|_| |_| \_n_/ |_|  

@author : naper
@description : c++ web framework

GNU LESSER GENERAL PUBLIC LICENSE
                       Version 3, 29 June 2007

 Copyright (C) 2007 Free Software Foundation, Inc. <http://fsf.org/>
 Everyone is permitted to copy and distribute verbatim copies
 of this license document, but changing it is not allowed.


  This version of the GNU Lesser General Public License incorporates
the terms and conditions of version 3 of the GNU General Public
License, supplemented by the additional permissions listed below.

  0. Additional Definitions.

  As used herein, "this License" refers to version 3 of the GNU Lesser
General Public License, and the "GNU GPL" refers to version 3 of the GNU
General Public License.

  "The Library" refers to a covered work governed by this License,
other than an Application or a Combined Work as defined below.

  An "Application" is any work that makes use of an interface provided
by the Library, but which is not otherwise based on the Library.
Defining a subclass of a class defined by the Library is deemed a mode
of using an interface provided by the Library.

  A "Combined Work" is a work produced by combining or linking an
Application with the Library.  The particular version of the Library
with which the Combined Work was made is also called the "Linked
Version".
=end

require 'socket'
require 'uri'
require File.expand_path('../Console/rf.console',__FILE__)
require File.expand_path('../Utils/error_message',__FILE__)

# Files will be served from this directory
#will be /var/mww/
WEB_ROOT = '/var/mww'

IP_SERVER = "127.0.0.1"
PORT_SERVER = 9090


# Map extensions to their content type
CONTENT_TYPE_MAPPING = {
  'html' => 'text/html',
  'htm' => 'text/html',
  'mw' => 'application/octet-stream',
  'txt' => 'text/plain',
  'css' => 'text/css',
  'png' => 'image/png',
  'js' => 'application/javascript',
  'jpg' => 'image/jpeg'
}

# Treat as binary data if content type cannot be found
DEFAULT_CONTENT_TYPE = 'application/octet-stream'

# This helper function parses the extension of the
# requested file and then looks up its content type.

def content_type(path)
  ext = File.extname(path).split(".").last
  CONTENT_TYPE_MAPPING.fetch(ext, DEFAULT_CONTENT_TYPE)
end

# This helper function parses the Request-Line and
# generates a path to a file on the server.

def requested_file(request_line)
  request_uri  = request_line.split(" ")[1]
  path         = URI.unescape(URI(request_uri).path)

  clean = []

  # Split the path into components
  parts = path.split("/")

  parts.each do |part|
    # skip any empty or current directory (".") path components
    next if part.empty? || part == '.'
    # If the path component goes up one directory level (".."),
    # remove the last clean component.
    # Otherwise, add the component to the Array of clean components
    part == '..' ? clean.pop : clean << part
  end

  # return the web root joined to the clean path
  File.join(WEB_ROOT, *clean)
end

# Except where noted below, the general approach of
# handling requests and generating responses is
# similar to that of the "Hello World" example
# shown earlier.

Console.header()
Console.print_action("Starting web server in #{IP_SERVER}:#{PORT_SERVER}")
server = TCPServer.new(IP_SERVER, PORT_SERVER)

begin

loop do
  socket       = server.accept
  request_line = socket.gets

  STDERR.puts request_line

  path = requested_file(request_line)
  path = File.join(path, 'index.html') if File.directory?(path)

  # Make sure the file exists and is not a directory
  # before attempting to open it.
  if File.exist?(path) && !File.directory?(path)
    Console.print_action("Opening #{path}")
    if(File.extname(path) == ".mw")
      #exec mw file as cgi bin
      output = IO.popen("#{path} >> tmp/__#{File.basename(path)}.txt")
      File.open("tmp/__#{File.basename(path)}.txt", "rb") do |file|
        socket.print "HTTP/1.1 200 OK\r\n" +
                   "Content-Type: text/html\r\n" +
                   "Content-Length: #{file.size}\r\n" +
                   "Connection: close\r\n"

        socket.print "\r\n"
        IO.copy_stream(file, socket)
        #delete tmp file
    end
  else
    File.open(path, "rb") do |file|
      socket.print "HTTP/1.1 200 OK\r\n" +
                   "Content-Type: #{content_type(file)}\r\n" +
                   "Content-Length: #{file.size}\r\n" +
                   "Connection: close\r\n"

      socket.print "\r\n"

      # write the contents of the file to the socket
      IO.copy_stream(file, socket)
    end
    end
  else
    Console.print_error("File not found")
    
    # respond with a 404 error code to indicate the file does not exist
    socket.print "HTTP/1.1 404 Not Found\r\n" +
                 "Content-Type: text/html\r\n" +
                 "Content-Length: #{NOTFOUND.show(path, IP_SERVER,PORT_SERVER).size}\r\n" +
                 "Connection: close\r\n"

    socket.print "\r\n"
    socket.print NOTFOUND.show(path, IP_SERVER,PORT_SERVER)
  end

  socket.close
end

rescue Exception => e 
  Console.print_error("Mwf server will be closed , #{e}")
end
