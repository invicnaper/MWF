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
class String
  def black;          "\033[30m#{self}\033[0m" end
  def red;            "\033[31m#{self}\033[0m" end
  def green;          "\033[32m#{self}\033[0m" end
  def brown;          "\033[33m#{self}\033[0m" end
  def blue;           "\033[34m#{self}\033[0m" end
  def magenta;        "\033[35m#{self}\033[0m" end
  def cyan;           "\033[36m#{self}\033[0m" end
  def gray;           "\033[37m#{self}\033[0m" end
  def bg_black;       "\033[40m#{self}\033[0m" end
  def bg_red;         "\033[41m#{self}\033[0m" end
  def bg_green;       "\033[42m#{self}\033[0m" end
  def bg_brown;       "\033[43m#{self}\033[0m" end
  def bg_blue;        "\033[44m#{self}\033[0m" end
  def bg_magenta;     "\033[45m#{self}\033[0m" end
  def bg_cyan;        "\033[46m#{self}\033[0m" end
  def bg_gray;        "\033[47m#{self}\033[0m" end
  def bold;           "\033[1m#{self}\033[22m" end
  def reverse_color;  "\033[7m#{self}\033[27m" end
end
module Console
  VERSION = '0.0.1'

  def Console.print_debug(string)
    puts "[" + "Debug".cyan + "] : #{string} .."
  end
  def Console.print_error(string)
    puts "[" + "Error".red + "] : #{string}"
  end
  def Console.print_done(string)
    puts "[" + "Ok".green + "] : #{string}"
  end
  def Console.print_action(string)
    puts "[" + "Action".magenta + "] : #{string}"
  end
  def Console.print_server(string)
    puts "[" + "Server".blue + "] : #{string}"
  end
  def Console.print_mysql(string)
    puts "[" + "Mysql".gray + "] : #{string}"
  end
  def Console.print_packet(string)
    puts "[" + "packet".brown + "] : #{string}"
  end
  def Console.print_plugin(string)
    puts "[" + "plugin".brown + "] : #{string}"
  end
  def Console.header
    puts "=================================================".cyan
    puts "        MWF web server        ".cyan
    puts "@Author : Naper".red
    puts "@Version : #{VERSION}".green
    puts "=================================================".cyan
  end
end