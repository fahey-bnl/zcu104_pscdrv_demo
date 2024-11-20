proc init {} {
  variable CFlags
  variable CPPFlags
  variable CXXFLAGS
  variable LDFlags

  variable Sources

}

proc setSources {} {
  variable Sources
  lappend Sources {../src "sources"}
}

proc doOnCreate {} {
  variable Config
  variable Sources
  variable TclPath
  addSources Sources

  ::fwfwk::printInfo "Customizing application BSP"

  domain active {app_domain}
  # add customizations here
  bsp config total_heap_size "1048576"
  bsp config minimal_stack_size "1024"
  bsp config max_task_name_len "32"
  bsp setlib -name lwip211
  bsp config api_mode "SOCKET_API"

  #end customizations
  bsp write
  bsp reload
  bsp regenerate
}

proc doOnBuild {} {}
