#!/usr/bin/env python

import BaseHTTPServer
import CGIHTTPServer
import cgitb;
cgitb.enable()

server = BaseHTTPServer.HTTPServer
handler = CGIHTTPServer.CGIHTTPRequestHandler

server_adress = ("localhost",8000)
handler.cgi_directories = ["./cgi"]

httpd = server(server_adress, handler)
httpd.serve_forever()
