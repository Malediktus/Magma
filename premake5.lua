workspace "Magma"
	architecture "x86_64"
	startproject "Client"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Magma"
include "Client"