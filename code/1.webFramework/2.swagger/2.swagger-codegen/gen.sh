#!/bin/bash

java -jar swagger-codegen-cli-2.4.9.jar generate -i swagger.yaml -l nodejs-server -o samples
