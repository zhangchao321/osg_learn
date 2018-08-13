cmake_minimum_required(VERSION 2.8.11)
 
if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif() 

PROJECT(RenderUseIndex)
SET(projectName RenderUseIndex)

set(CMAKE_AUTOMOC ON)
 
#############osg######################
SET (OSG_Dir  "" CACHE PATH "OSG_Dir")
if("${OSG_Dir}" STREQUAL "")
  MESSAGE (FATAL_ERROR "NOT FOUND: OSG_Dir" )
endif() 

SET(Osg_INCLUDE  ${OSG_Dir}/include)
SET(Osg_lib   "${OSG_Dir}/lib/*d.lib")
  
##############source####################
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR} 
	${Osg_INCLUDE} 
) 

file(GLOB QT_WRAP *.h  )  
file(GLOB HeaderFile ${CMAKE_CURRENT_SOURCE_DIR}/*h)
file(GLOB SrcFile ${CMAKE_CURRENT_SOURCE_DIR}/*cpp )
##vs filter
SOURCE_GROUP("occ" FILES
    ${ExportOccHeaderFile}
	${ExportOccSrcFile}
) 

SOURCE_GROUP("Generated" FILES 
  ${MOCSrcs} 
)


add_executable(${projectName} 
  ${HeaderFile} 
  ${SrcFile} 
)   
TARGET_LINK_LIBRARIES(${projectName} ${Osg_lib} ) 


