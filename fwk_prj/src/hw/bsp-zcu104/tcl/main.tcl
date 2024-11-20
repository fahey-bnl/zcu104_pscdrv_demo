################################################################################
# Main tcl for the module
################################################################################

# ==============================================================================
proc init {} {
}

# ==============================================================================
proc setSources {} {
  variable Sources
  lappend Sources {../hdl/design_1_wrapper.vhd "vhdl"}
}

# ==============================================================================

proc doOnCreate {} {
  variable Sources
  variable TclPath
  
  source ${TclPath}/design_1.tcl
  addSources "Sources"
}

proc setPrjProperties {} {
  set_property part xczu7ev-ffvc1156-2-e [current_project]
  set_property target_language VHDL [current_project]
  set_property default_lib xil_defaultlib [current_project]
  set_property board_part xilinx.com:zcu104:part0:1.1 [current_project]
}

# ==============================================================================
proc doOnBuild {} {
}

# ==============================================================================
proc setSim {} {
}

proc setAddressSpace {} {
}

# ==============================================================================
