####### Start adding the googletest #######
set(gtest_force_shared_crt ON CACHE BOOL "Use shared CRT" FORCE)

add_subdirectory(googletest)
####### End adding the googletest #######

####### Start adding the json #######
add_subdirectory(json)
####### End adding the json #######

