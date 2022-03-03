#!/bin/bash

REQUEST_METHOD='POST'
CONTENT_LENGTH=70
QUERY_STRING='choix_capteur=lum1&range_lum=50&on_off=on&password=1234&code_maison=A'
export CONTENT_LENGTH
export REQUEST_METHOD
echo $QUERY_STRING | ./config.cgi
