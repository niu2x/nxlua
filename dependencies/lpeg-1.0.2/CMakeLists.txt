add_library(lpeg STATIC "")
target_sources(lpeg PRIVATE
	"lpcap.c"
	"lpcode.c"
	"lpprint.c"
	"lptree.c"
	"lpvm.c"
)

target_link_libraries(lpeg lua-5.1.5)