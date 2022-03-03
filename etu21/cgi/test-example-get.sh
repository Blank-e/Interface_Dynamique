#!/bin/bash
REQUEST_METHOD='GET'
QUERY_STRING='choix_capteur=temp1&val_min=-10.0&val_max=20.0&unite=celsius&on_off=on&password=1234'
export QUERY_STRING
export REQUEST_METHOD
./config.cgi
