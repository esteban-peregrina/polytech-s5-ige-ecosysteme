#!/bin/bash

### Dynamic setup ###

# Enable error signals
set -e

# Print and execute passed arguments
echo "Provided arguments : $@"
exec $@