index.rst:
	echo "API" > $@
	echo "===" >> $@
	echo "" >> $@
	echo ".. toctree::" >> $@
	echo "" >> $@
	ls *.rst|grep -v index.rst|sort|sed 's/.rst//g'|awk '{print "   " $$1 }' >> $@

.PHONY: index.rst	