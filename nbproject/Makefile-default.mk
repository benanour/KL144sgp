#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MX170pg12sgp.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MX170pg12sgp.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=ADCbn32.C BIT16_HEX4.C DS3231v2.c HDC1080v2.C I2C1BN.c LockUnlock.c MCP79411.c NokiaDrv2.c NokiaScr.c PG_12sgp.C SCD40.c SPI1.C eeprom24.c uart1bn.c SGP30.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/ADCbn32.o ${OBJECTDIR}/BIT16_HEX4.o ${OBJECTDIR}/DS3231v2.o ${OBJECTDIR}/HDC1080v2.o ${OBJECTDIR}/I2C1BN.o ${OBJECTDIR}/LockUnlock.o ${OBJECTDIR}/MCP79411.o ${OBJECTDIR}/NokiaDrv2.o ${OBJECTDIR}/NokiaScr.o ${OBJECTDIR}/PG_12sgp.o ${OBJECTDIR}/SCD40.o ${OBJECTDIR}/SPI1.o ${OBJECTDIR}/eeprom24.o ${OBJECTDIR}/uart1bn.o ${OBJECTDIR}/SGP30.o
POSSIBLE_DEPFILES=${OBJECTDIR}/ADCbn32.o.d ${OBJECTDIR}/BIT16_HEX4.o.d ${OBJECTDIR}/DS3231v2.o.d ${OBJECTDIR}/HDC1080v2.o.d ${OBJECTDIR}/I2C1BN.o.d ${OBJECTDIR}/LockUnlock.o.d ${OBJECTDIR}/MCP79411.o.d ${OBJECTDIR}/NokiaDrv2.o.d ${OBJECTDIR}/NokiaScr.o.d ${OBJECTDIR}/PG_12sgp.o.d ${OBJECTDIR}/SCD40.o.d ${OBJECTDIR}/SPI1.o.d ${OBJECTDIR}/eeprom24.o.d ${OBJECTDIR}/uart1bn.o.d ${OBJECTDIR}/SGP30.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/ADCbn32.o ${OBJECTDIR}/BIT16_HEX4.o ${OBJECTDIR}/DS3231v2.o ${OBJECTDIR}/HDC1080v2.o ${OBJECTDIR}/I2C1BN.o ${OBJECTDIR}/LockUnlock.o ${OBJECTDIR}/MCP79411.o ${OBJECTDIR}/NokiaDrv2.o ${OBJECTDIR}/NokiaScr.o ${OBJECTDIR}/PG_12sgp.o ${OBJECTDIR}/SCD40.o ${OBJECTDIR}/SPI1.o ${OBJECTDIR}/eeprom24.o ${OBJECTDIR}/uart1bn.o ${OBJECTDIR}/SGP30.o

# Source Files
SOURCEFILES=ADCbn32.C BIT16_HEX4.C DS3231v2.c HDC1080v2.C I2C1BN.c LockUnlock.c MCP79411.c NokiaDrv2.c NokiaScr.c PG_12sgp.C SCD40.c SPI1.C eeprom24.c uart1bn.c SGP30.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/MX170pg12sgp.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX170F256B
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/ADCbn32.o: ADCbn32.C  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ADCbn32.o.d 
	@${RM} ${OBJECTDIR}/ADCbn32.o 
	@${FIXDEPS} "${OBJECTDIR}/ADCbn32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ADCbn32.o.d" -o ${OBJECTDIR}/ADCbn32.o ADCbn32.C    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/BIT16_HEX4.o: BIT16_HEX4.C  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BIT16_HEX4.o.d 
	@${RM} ${OBJECTDIR}/BIT16_HEX4.o 
	@${FIXDEPS} "${OBJECTDIR}/BIT16_HEX4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BIT16_HEX4.o.d" -o ${OBJECTDIR}/BIT16_HEX4.o BIT16_HEX4.C    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/DS3231v2.o: DS3231v2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DS3231v2.o.d 
	@${RM} ${OBJECTDIR}/DS3231v2.o 
	@${FIXDEPS} "${OBJECTDIR}/DS3231v2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/DS3231v2.o.d" -o ${OBJECTDIR}/DS3231v2.o DS3231v2.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/HDC1080v2.o: HDC1080v2.C  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HDC1080v2.o.d 
	@${RM} ${OBJECTDIR}/HDC1080v2.o 
	@${FIXDEPS} "${OBJECTDIR}/HDC1080v2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/HDC1080v2.o.d" -o ${OBJECTDIR}/HDC1080v2.o HDC1080v2.C    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/I2C1BN.o: I2C1BN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/I2C1BN.o.d 
	@${RM} ${OBJECTDIR}/I2C1BN.o 
	@${FIXDEPS} "${OBJECTDIR}/I2C1BN.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/I2C1BN.o.d" -o ${OBJECTDIR}/I2C1BN.o I2C1BN.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/LockUnlock.o: LockUnlock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LockUnlock.o.d 
	@${RM} ${OBJECTDIR}/LockUnlock.o 
	@${FIXDEPS} "${OBJECTDIR}/LockUnlock.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/LockUnlock.o.d" -o ${OBJECTDIR}/LockUnlock.o LockUnlock.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/MCP79411.o: MCP79411.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/MCP79411.o.d 
	@${RM} ${OBJECTDIR}/MCP79411.o 
	@${FIXDEPS} "${OBJECTDIR}/MCP79411.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/MCP79411.o.d" -o ${OBJECTDIR}/MCP79411.o MCP79411.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/NokiaDrv2.o: NokiaDrv2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/NokiaDrv2.o.d 
	@${RM} ${OBJECTDIR}/NokiaDrv2.o 
	@${FIXDEPS} "${OBJECTDIR}/NokiaDrv2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/NokiaDrv2.o.d" -o ${OBJECTDIR}/NokiaDrv2.o NokiaDrv2.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/NokiaScr.o: NokiaScr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/NokiaScr.o.d 
	@${RM} ${OBJECTDIR}/NokiaScr.o 
	@${FIXDEPS} "${OBJECTDIR}/NokiaScr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/NokiaScr.o.d" -o ${OBJECTDIR}/NokiaScr.o NokiaScr.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/PG_12sgp.o: PG_12sgp.C  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PG_12sgp.o.d 
	@${RM} ${OBJECTDIR}/PG_12sgp.o 
	@${FIXDEPS} "${OBJECTDIR}/PG_12sgp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PG_12sgp.o.d" -o ${OBJECTDIR}/PG_12sgp.o PG_12sgp.C    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/SCD40.o: SCD40.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SCD40.o.d 
	@${RM} ${OBJECTDIR}/SCD40.o 
	@${FIXDEPS} "${OBJECTDIR}/SCD40.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/SCD40.o.d" -o ${OBJECTDIR}/SCD40.o SCD40.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/SPI1.o: SPI1.C  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SPI1.o.d 
	@${RM} ${OBJECTDIR}/SPI1.o 
	@${FIXDEPS} "${OBJECTDIR}/SPI1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/SPI1.o.d" -o ${OBJECTDIR}/SPI1.o SPI1.C    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/eeprom24.o: eeprom24.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/eeprom24.o.d 
	@${RM} ${OBJECTDIR}/eeprom24.o 
	@${FIXDEPS} "${OBJECTDIR}/eeprom24.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/eeprom24.o.d" -o ${OBJECTDIR}/eeprom24.o eeprom24.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/uart1bn.o: uart1bn.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart1bn.o.d 
	@${RM} ${OBJECTDIR}/uart1bn.o 
	@${FIXDEPS} "${OBJECTDIR}/uart1bn.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uart1bn.o.d" -o ${OBJECTDIR}/uart1bn.o uart1bn.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/SGP30.o: SGP30.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SGP30.o.d 
	@${RM} ${OBJECTDIR}/SGP30.o 
	@${FIXDEPS} "${OBJECTDIR}/SGP30.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/SGP30.o.d" -o ${OBJECTDIR}/SGP30.o SGP30.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/ADCbn32.o: ADCbn32.C  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ADCbn32.o.d 
	@${RM} ${OBJECTDIR}/ADCbn32.o 
	@${FIXDEPS} "${OBJECTDIR}/ADCbn32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ADCbn32.o.d" -o ${OBJECTDIR}/ADCbn32.o ADCbn32.C    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/BIT16_HEX4.o: BIT16_HEX4.C  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BIT16_HEX4.o.d 
	@${RM} ${OBJECTDIR}/BIT16_HEX4.o 
	@${FIXDEPS} "${OBJECTDIR}/BIT16_HEX4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BIT16_HEX4.o.d" -o ${OBJECTDIR}/BIT16_HEX4.o BIT16_HEX4.C    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/DS3231v2.o: DS3231v2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DS3231v2.o.d 
	@${RM} ${OBJECTDIR}/DS3231v2.o 
	@${FIXDEPS} "${OBJECTDIR}/DS3231v2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/DS3231v2.o.d" -o ${OBJECTDIR}/DS3231v2.o DS3231v2.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/HDC1080v2.o: HDC1080v2.C  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HDC1080v2.o.d 
	@${RM} ${OBJECTDIR}/HDC1080v2.o 
	@${FIXDEPS} "${OBJECTDIR}/HDC1080v2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/HDC1080v2.o.d" -o ${OBJECTDIR}/HDC1080v2.o HDC1080v2.C    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/I2C1BN.o: I2C1BN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/I2C1BN.o.d 
	@${RM} ${OBJECTDIR}/I2C1BN.o 
	@${FIXDEPS} "${OBJECTDIR}/I2C1BN.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/I2C1BN.o.d" -o ${OBJECTDIR}/I2C1BN.o I2C1BN.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/LockUnlock.o: LockUnlock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LockUnlock.o.d 
	@${RM} ${OBJECTDIR}/LockUnlock.o 
	@${FIXDEPS} "${OBJECTDIR}/LockUnlock.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/LockUnlock.o.d" -o ${OBJECTDIR}/LockUnlock.o LockUnlock.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/MCP79411.o: MCP79411.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/MCP79411.o.d 
	@${RM} ${OBJECTDIR}/MCP79411.o 
	@${FIXDEPS} "${OBJECTDIR}/MCP79411.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/MCP79411.o.d" -o ${OBJECTDIR}/MCP79411.o MCP79411.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/NokiaDrv2.o: NokiaDrv2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/NokiaDrv2.o.d 
	@${RM} ${OBJECTDIR}/NokiaDrv2.o 
	@${FIXDEPS} "${OBJECTDIR}/NokiaDrv2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/NokiaDrv2.o.d" -o ${OBJECTDIR}/NokiaDrv2.o NokiaDrv2.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/NokiaScr.o: NokiaScr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/NokiaScr.o.d 
	@${RM} ${OBJECTDIR}/NokiaScr.o 
	@${FIXDEPS} "${OBJECTDIR}/NokiaScr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/NokiaScr.o.d" -o ${OBJECTDIR}/NokiaScr.o NokiaScr.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/PG_12sgp.o: PG_12sgp.C  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PG_12sgp.o.d 
	@${RM} ${OBJECTDIR}/PG_12sgp.o 
	@${FIXDEPS} "${OBJECTDIR}/PG_12sgp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PG_12sgp.o.d" -o ${OBJECTDIR}/PG_12sgp.o PG_12sgp.C    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/SCD40.o: SCD40.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SCD40.o.d 
	@${RM} ${OBJECTDIR}/SCD40.o 
	@${FIXDEPS} "${OBJECTDIR}/SCD40.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/SCD40.o.d" -o ${OBJECTDIR}/SCD40.o SCD40.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/SPI1.o: SPI1.C  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SPI1.o.d 
	@${RM} ${OBJECTDIR}/SPI1.o 
	@${FIXDEPS} "${OBJECTDIR}/SPI1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/SPI1.o.d" -o ${OBJECTDIR}/SPI1.o SPI1.C    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/eeprom24.o: eeprom24.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/eeprom24.o.d 
	@${RM} ${OBJECTDIR}/eeprom24.o 
	@${FIXDEPS} "${OBJECTDIR}/eeprom24.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/eeprom24.o.d" -o ${OBJECTDIR}/eeprom24.o eeprom24.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/uart1bn.o: uart1bn.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart1bn.o.d 
	@${RM} ${OBJECTDIR}/uart1bn.o 
	@${FIXDEPS} "${OBJECTDIR}/uart1bn.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uart1bn.o.d" -o ${OBJECTDIR}/uart1bn.o uart1bn.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/SGP30.o: SGP30.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SGP30.o.d 
	@${RM} ${OBJECTDIR}/SGP30.o 
	@${FIXDEPS} "${OBJECTDIR}/SGP30.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/SGP30.o.d" -o ${OBJECTDIR}/SGP30.o SGP30.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/MX170pg12sgp.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE) -g -mdebugger -DPICkit3PlatformTool=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MX170pg12sgp.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=PICkit3PlatformTool=1,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/MX170pg12sgp.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MX170pg12sgp.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/MX170pg12sgp.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
