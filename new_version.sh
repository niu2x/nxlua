#!/bin/bash
version=$1

if [ -z "$version" ]; then
	echo "usage: $0 version"
	exit 1
fi

echo $version > VERSION

git commit VERSION -m "update version to $version"

git tag "v${version}"