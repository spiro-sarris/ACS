#!/bin/bash
acsncDelChannelsInNameS --name_service corbaloc::$HOST:3001/NameService --notify_service "$1" --baseport 0
