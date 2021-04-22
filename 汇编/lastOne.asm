DATAS SEGMENT
;常数定义区
    studentIdNum=8
    studentNameNum=20
    subjectNum=3
    classStuNum=30
    passwordNum=5
    studentSpace=TYPE student
    password DB "ADMIN"
;结构体定义
student STRUCT
    studentId BYTE studentIdNum+1 DUP(?)
    studentName BYTE studentNameNum DUP(?)
    score WORD subjectNum DUP(?)
    totalSCore WORD 0    
student ENDS
;消息定义区,  s[消息内容梗要]
    sChangeline BYTE 0dh,0ah,'$'
    sInputPassword BYTE "Input password to enter system:$"
    sWrongPassword BYTE "Password input wrong!",0dh,0ah,'$'
    sStudentNumMax BYTE "Oops, there are to much student information in this sysytem, you can\'t add more.",0dh,0ah,'$'
    sInputStuId BYTE "Plz input a 8 number student ID:$"
    sInputStuName BYTE "Plz input student name:$"
    sInputStuScore BYTE "Plz input student score:$"
    sInputWrongScore BYTE "[Wrong Input] Has been processed automatically, the data will not be recorded.",0dh,0ah,'$'
    sLogSysFail BYTE "Password input wrong!You got no rights to enter this student system!",0dh,0ah,'$'
    sGoodByeMSG BYTE 0dh,0ah,"-->Thanks for your using!<--",0dh,0ah,'$'
    sTeacherMenu BYTE "------------------------------------------",0dh,0ah
                 BYTE "    1:Add student Information",0dh,0ah
                 BYTE "    2:Print all student infomation",0dh,0ah
                 BYTE "    3:Print student list by sum score",0dh,0ah
                 BYTE "    4:Data anl",0dh,0ah
                 BYTE "    5:Search student",0dh,0ah
                 BYTE "    6:Exit student file system",0dh,0ah
                 BYTE "------------------------------------------",0dh,0ah
                 BYTE "Input your choice:$"
    sPrintStuID BYTE "Stundent ID:$"
    sPrintStuName BYTE "Student name:$"
    sPrintStuSCore BYTE "Student score:$"
    sPrintByScore BYTE "Student list arrange by score $"
    sPrintSumScore BYTE "This subject sum score:$"
    sPrintAverScore BYTE "This subject average score:$"
    sCantFInd BYTE "OOOOOOpppppsssss，can't find this student!",0dh,0ah,'$'
    sPrintZeTOSix BYTE "0~60 has:$"
    sPrintSixTOSev BYTE "60~70 has:$"
    sPrintSevTOEig BYTE "70~80 has:$"
    sPrintEIGTOSix BYTE "80~90 has:$"
    sPrintNinAbove BYTE "90~ has:$"

    sPause BYTE "Press any key to contiune!",0dh,0ah,'$'

;数据定义区于
    studentNum WORD 0
    class student classStuNum DUP(< >)
    score1List WORD classStuNum DUP(?)
    score2List WORD classStuNum DUP(?)
    score3List WORD classStuNum DUP(?)
    totalSCoreList WORD classStuNum DUP(?)
    scoreTotal WORD subjectNum DUP(0)
    ZEROTOSIX WORD 0
    SIXTOSEV WORD 0
    SEVTOEIG WORD 0
    EIGTONIN WORD 0
    NINTOONE WORD 0
    FLOAT WORD 2 DUP(?)
    lastStuAdress WORD class
    nameBuf BYTE studentNameNum DUP(?)
    strBuffer BYTE 20
              BYTE ?
              BYTE 20 DUP(?)
    caseTeacherTable WORD pageAddStudentInfo
                     WORD pagePrintStuInfo
                     WORD pagePrintListByTotal
                     WORD pageDataAnl
                     WORD pageSearchStu
    
DATAS ENDS

STACKS SEGMENT
    ;此处输入堆栈段代码
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    CALL PAGELOG
    CALL FOChangeLine
    CMP DX,0
    JZ failLogIn
;主程序实现地点 
MainTeaLoop:
    LEA BX,sTeacherMenu
    CALL pageMainMenu
    CMP DX,6
    JZ exitSystem
    CMP DX,7
    JZ MainTeaLoop
    MOV SI,DX
    DEC SI
    SAL SI,1
    CALL caseTeacherTable[SI]
    JMP MainTeaLoop
;结束运行
    JMP exitSystem
failLogIn:
    CALL PAGELogFail
exitSystem:
    LEA BX,sGoodByeMSG
    CALL pageExit
    MOV AH,4CH
    INT 21H
;函数
;[P]登陆,DX为1则登陆成功
PAGELOG PROC
    PUSH CX
    PUSH AX
    PUSH SI
    PUSH BX
    MOV CX,3                        ;最大的输入次数
PASSWORDEXAM:                       ;一次输入循环
    LEA BX,sInputPassword           ;提示信息的输出
    CALL FOMSG
    PUSH CX
    MOV SI,0
    MOV CX,passwordNum
PASSWORDINPUT:                      ;密码的输入，检测
    MOV AH,08H
    INT 21H
    MOV BL,'*'
    CALL FOChar
    CMP AL,password[SI]
    JNZ UNCORRECT
    INC SI
    LOOP PASSWORDINPUT
    JMP CORRECT                     ;密码输入正确
UNCORRECT:                          ;密码错误
    CALL FOChangeLine
    LEA BX,sWrongPassword           ;提示信息的输出
    CALL FOMSG
    POP CX
    LOOP PASSWORDEXAM
    MOV DX,0
    JMP PAGELOGEND
CORRECT:
    POP CX
    MOV DX,1
PAGELOGEND:
    POP BX
    POP SI
    POP AX
    POP CX
    RET
PAGELOG ENDP
;[P]密码错误
PAGELogFail PROC
    LEA BX,sLogSysFail
    CALL FOMSG
    RET
PAGELogFail ENDP
;[p]主菜单,使用DX返回选择信息，BX约定为菜单的选项信息的存储地址
pageMainMenu PROC
    PUSH AX
    CALL FOMSG
    MOV AH,01H
    INT 21H
    CALL FOChangeLine
    CMP AL,'1'
    JB wrongCHO
    CMP AL,'6'
    JA wrongCHO
    SUB AL,'0'
    CBW
    MOV DX,AX
    JMP pageMainMenuEnd
wrongCHO:
    MOV DX,7
    JMP pageMainMenuEnd
pageMainMenuEnd:
    POP AX
    RET
pageMainMenu ENDP  
;[p]添加学生信息页面
pageAddStudentInfo proc
    PUSH SI
    PUSH DI
    PUSH CX
    PUSH AX
    CMP studentNum,30
    JA maxStuInfo
;---------------------------------------
    LEA BX,sInputStuId          ;输入学号
    CALL FOMSG              
    MOV BX,[lastStuAdress]      
    MOV DX,studentIdNum
    CALL FIString               
    CALL FOChangeLine           
;---------------------------------------    
    LEA BX,sInputStuName        ;输入姓名
    CALL FOMSG
    MOV BX,[lastStuAdress]
    ADD BX,studentIdNum+1 
    MOV DX,studentNameNum
    CALL FIString_CGLIne     
    CALl FOChangeLine
;---------------------------------------   
    LEA BX,sInputStuScore       ;输入成绩
    CALL FOMSG
    MOV CX,subjectNum
    MOV SI,0
    MOV BX,[lastStuAdress]
    ADD BX,studentIdNum+1
    ADD BX,studentNameNum
scoreInLoop:
    PUSH BX
    CALl FINum10
    CMP DX,0
    JZ wrongScoreIn
    MOV DX,BX
    POP BX
    MOV [BX][SI],DX
    ADD scoreTotal[SI],DX                   ;单科数据的合计增加
    ADD [BX][subjectNum*2],DX
    INC SI
    INC SI
    LOOP scoreInLoop
    CALl FOChangeLine
;---------------------------------------
    LEA BX,score1List                       ;更新数据分析表
    MOV AX,studentIdNum+studentNameNum+1
    MOV DX,[lastStuAdress]
    CALL FAsertData
    LEA BX,score2List                       ;更新数据分析表
    MOV AX,studentIdNum+studentNameNum+3
    MOV DX,[lastStuAdress]
    CALL FAsertData
    LEA BX,score3List                       ;更新数据分析表
    MOV AX,studentIdNum+studentNameNum+5
    MOV DX,[lastStuAdress]
    CALL FAsertData
    MOV BX,[lastStuAdress]
    MOV SI,studentNum
    SHL SI,1
    MOV totalSCoreList[SI],BX
;---------------------------------------    
    ADD lastStuAdress,studentSpace          ;数据更新
    INC studentNum
;---------------------------------------    
    JMP pageAddStudentInfoEnd
wrongScoreIn:
    lea BX,sInputWrongScore
    CALl FOMSG
    JMP scoreInLoop
maxStuInfo:
    LEA BX,sStudentNumMax
    CALL FOMSG
pageAddStudentInfoEnd:
    POP AX
    POP CX
    POP DI
    POP SI
    RET
pageAddStudentInfo ENDP
;[P]输出学生信息，乱序
pagePrintStuInfo PROC
    CALL FOStuInfoAll
    RET
pagePrintStuInfo ENDP
;[P]按照学生的总成绩排序输出
pagePrintListByTotal PROC
    PUSH DI
    PUSH SI
    PUSH BX
    MOV SI,0
    MOV DI,studentNum
    SHL DI,1
    SUB DI,2
    LEA BX,totalSCoreList
    CALl QuickSort
    LEA BX,totalSCoreList
    CALL FOStuInfoBySCore
    POP BX
    POP SI
    POP DI
    RET
pagePrintListByTotal ENDP
;[p]数据分析
pageDataAnl PROC 
;------------------------------------   输出学生按照第1门课成绩排序
    LEA BX,sPrintByScore
    CALL FOMSG
    MOV BX,'1'
    CALL FOChangeLine
    LEA BX,score1List
    CALL FOStuInfoBySCore
    LEA BX,sPause
    CALL FOMSG
    MOV AH,01H
    INT 21H
;------------------------------------   输出1总成绩
    LEA BX,sPrintSumScore
    CALL FOMSG
    MOV BX,scoreTotal[0]
    CALL FONum10
    CALL FOChangeLine
;------------------------------------

    ;LEA BX,sPrintAverScore
    ;CALL FOMSG
    ;MOV DX,0
    ;MOV AX,totalSCore
   ; MOV CX,studentNum
   ; DIV CL
   ; CBW
  ;  MOV BX,AX 
  ;  CALL FONum10
  ;  CALL FOChangeLine
    ;MUL CX
    ;CALL ToFloat
    ;MOV BX,FLOAT[0]
    ;CALL FONum10
    ;MOV BX,FLOAT[2]
    
    ;CALL PRINTFLOAT
    
;------------------------------------   输出第1门成绩的分数段
    LEA BX,class
    MOV AX,studentNameNum+studentIdNum+1
    CALL FAdataAnl
    CALL FORangeOfSCore
    LEA BX,sPause
    CALL FOMSG
    MOV AH,01H
    INT 21H
;------------------------------------   输出学生按照第2门课成绩排序
    LEA BX,sPrintByScore
    CALL FOMSG
    MOV BX,'2'
    CALL FOChangeLine
    LEA BX,score2List
    CALL FOStuInfoBySCore
    LEA BX,sPause
    CALL FOMSG
    MOV AH,01H
    INT 21H
;------------------------------------   输出2总成绩
    LEA BX,sPrintSumScore
    CALL FOMSG
    MOV BX,scoreTotal[2]
    CALL FONum10
    CALL FOChangeLine
;-------
    ;LEA BX,sPrintAverScore
    ;CALL FOMSG
    ;MOV CX,100
    ;MOV AX,totalSCore[2]
    ;MUL CX
    ;MOV CX,studentNum
    ;DIV CX
    ;CALL ToFloat
    ;CALL PRINTFLOAT
    ;CALL FOChangeLine
;------------------------------------   输出第2门成绩的分数段
    LEA BX,class
    MOV AX,studentNameNum+studentIdNum+3
    CALL FAdataAnl
    CALL FORangeOfSCore
    LEA BX,sPause
    CALL FOMSG
    MOV AH,01H
    INT 21H
;------------------------------------   输出学生按照第3门课成绩排序
    LEA BX,sPrintByScore
    CALL FOMSG
    MOV BX,'3'
    CALL FOChangeLine
    LEA BX,score3List
    CALL FOStuInfoBySCore
    LEA BX,sPause
    CALL FOMSG
    MOV AH,01H
    INT 21H
;------------------------------------   输出3总成绩
    LEA BX,sPrintSumScore
    CALL FOMSG
    MOV BX,scoreTotal[4]
    CALL FONum10
    CALL FOChangeLine
;------------------------------------
    ;LEA BX,sPrintAverScore
    ;CALL FOMSG
    ;MOV CX,100
    ;MOV AX,totalSCore[4]
    ;MUL CX
    ;MOV CX,studentNum
    ;;DIV CX
   ; CALL ToFloat
    ;CALL PRINTFLOAT
;------------------------------------   输出第3门成绩的分数段
    LEA BX,class
    MOV AX,studentNameNum+studentIdNum+5
    CALL FAdataAnl
    CALL FORangeOfSCore
    LEA BX,sPause
    CALL FOMSG
    MOV AH,01H
    INT 21H

    RET
pageDataAnl ENDP
;[P]搜索学生
pageSearchStu PROC
    CALL SearchStudentName
    RET
pageSearchStu ENDP
;[P]结束页面,约定BX为结束问候语的存储地址
pageExit PROC
    CALL FOMSG
    RET
pageExit ENDP

;算法子程序
;[F]插入数据，只存地址，不移动数据，约定BX为排好序的数据队列首地址，AX为排序基准元素数据偏移量,DX为数据地址，同时数据均为WORD
;BX作为插入时目前对应的信息地址存储的地址
FAsertData PROC
    PUSH CX
    PUSH SI
    PUSH DI
    CMP studentNum,0
    JZ firstSert
;--------------------------------------- 
    MOV SI,AX               ;比较数据偏移量保存于SI
;--------------------------------------- 
    MOV AX,studentNum       ;此时学生数目还未增加，故仅需减去1，乘上2即可得到最后的地址
    DEC AX
    SAL AX,1
    ADD BX,AX               ;找到排列数组最后的地址
;--------------------------------------- 
    PUSH BX  
    MOV BX,DX 
    MOV AX,[BX][SI]         ;获取插入数据的待比较数据
    POP BX
;--------------------------------------- 
    MOV CX,studentNum       ;最多比较数据次数
sertDataLoop:;获得待插入位置
    PUSH BX
    MOV DI,[BX]
    MOV BX,DI
    CMP AX,[BX][SI]
    JB findSertPos
    POP BX
    MOV DI,[BX]
    MOV [BX+2],DI
    DEC BX
    DEC BX
    LOOP sertDataLoop
    JMP justSert
findSertPos:
    POP BX
justSert:
    MOV [BX+2],DX
    JMP fasertEnd
firstSert:
    MOV [BX],DX
fasertEnd:
    POP DI
    POP SI
    POP CX
    RET
FAsertData ENDP
;[F]求平均分以及最后的数据分段，约定BX为数据起始地址，AX为数据偏移地址,约定数据段的三个统计量为数据存储地址
FAdataAnl PROC
    PUSH SI
    MOV ZEROTOSIX,0
    MOV SIXTOSEV,0
    MOV SEVTOEIG,0
    MOV EIGTONIN,0
    MOV NINTOONE,0
    MOV SI,AX
    MOV CX,studentNum
sperateScoreLoop:
    CMP [BX][SI],60
    JA scoreAbove60
    INC ZEROTOSIX
    JMP sperateOneEnd
scoreAbove60:
    CMP [BX][SI],70
    JA scoreAbove70
    INC SIXTOSEV
    JMP sperateOneEnd
scoreAbove70:
    CMP [BX][SI],80
    JA scoreAbove80
    INC SEVTOEIG
    JMP sperateOneEnd
scoreAbove80:
    CMP [BX][SI],90
    JA scoreAbove90
    INC EIGTONIN
    JMP sperateOneEnd
scoreAbove90:
    INC NINTOONE
sperateOneEnd:
    ADD BX,studentSpace
    LOOP sperateScoreLoop
    POP SI
    RET
FAdataAnl ENDP
;---------------------排序----------------
;MOV SI,0
;MOV DI,studentNum*2-2
;LEA BX,TOTAL...
QuickSort PROC
    
	CMP SI,DI
	JGE QuickSortOver
	CALL Partition

	PUSH AX
	PUSH SI
	PUSH DI
	SUB AX,2
	MOV DI,AX
	CALL QuickSort
    
	POP DI 
	POP SI
	POP AX
	ADD AX,2
	MOV SI,AX
	CALL QuickSort

QuickSortOver:
	RET
QuickSort ENDP
;小下标传入SI，大下标传入DI，数组地址传入BX
Partition PROC  
	PUSH DI
	PUSH SI
	PUSH CX 
    PUSH [BX][SI]

    PUSH BX
    PUSH DI
    MOV DI,[BX][SI]
    MOV BX,DI
	MOV	AX,[BX].totalSCore;LEA BX,CLASS
    POP DI
    POP BX

PartitionLOOP:
	CMP SI,DI
	JGE PartitionOver
RightPart:
	CMP SI,DI
	JGE	NotBig

    PUSH BX
    PUSH SI
    MOV SI,[BX][DI]
    MOV BX,SI
	CMP [BX].totalSCore,AX
    POP SI
    POP BX

	JL NotBig
	SUB	DI,2;studentSpace
	JMP RightPart
NotBig:
	MOV CX,[BX][DI]
	MOV	[BX][SI],CX
LeftPart:
	CMP SI,DI
	JGE	NotSmall

    PUSH BX
    PUSH DI
	MOV DI,[BX][SI]
    MOV BX,DI
	CMP [BX].totalSCore,AX
    POP DI
    POP BX

	JG	NotSmall
	ADD	SI,2;studentSpace
	JMP LeftPart
NotSmall:
	MOV CX,[BX][SI]
	MOV	[BX][DI],CX
	JMP PartitionLOOP

PartitionOver:
    POP [BX][DI]
	MOV	AX,SI
	POP CX
	POP	SI 
	POP DI
	RET
Partition ENDP
;-------------------------------------
SearchStudentName proc
    PUSH CX
    PUSH AX
    PUSH SI
    PUSH DI

    MOV DX,studentNameNum
    LEA BX,nameBuf
    call FIString_CGLIne
    PUSH DS 
    POP ES
    MOV CX,studentNum
    MOV SI,0
    MOV BX,totalSCoreList[0]
    PUSH SI
SearchStudentNameLOOP:
    
    LEA SI,nameBuf
    LEA DI,[BX].studentName

    PUSH CX
    MOV CX,studentNameNum
    CLD
    REPE CMPSB
    POP CX

    JZ haveThisOne
    POP SI
    ADD SI,2
    MOV BX,totalSCoreList[SI]
    PUSH SI
    LOOP SearchStudentNameLOOP
    POP SI
    JMP haveNOne
haveThisOne:
    POP SI
    CALL FOStudentInfo
haveNOne:
    LEA BX,sCantFInd
    CALL FOMSG
    CALL FOChangeLine
    POP DI
    POP SI
    POP AX 
    POP CX
    ret
SearchStudentName endp
;-----------------
ToFloat	PROC
	PUSH DX
	PUSH CX

	MOV DX,0
	MOV	BX,10
	MOV	CX,2
FLOATLOOP1:
	DIV	 BX
	PUSH DX

	MOV  DX,0
	LOOP	FLOATLOOP1
	MOV	FLOAT[0],AX
	MOV	CX,2
	MOV	AX,0
FLOATLOOP2:
	MUL	BX
	POP	DX
	ADD	AX,DX
	MOV	DX,0
	LOOP	FLOATLOOP2
	MOV	FLOAT[2],AX

	POP CX
	POP	DX
	RET
ToFloat	ENDP
PRINTFLOAT PROC 
	PUSH DX
	PUSH BX
	MOV	BX,FLOAT[0]
	CALL FONum10

	MOV	DL,2EH
	MOV	AH,02H
	INT 21H
	MOV BX,FLOAT[2]
	CALL FONum10
	
	POP BX
	POP DX
	RET
PRINTFLOAT ENDP

;I/0子程序
;[F]10进制输入，约定BX为返回数字，DX为返回状态，Dx为0输入错误，Dx为1空格结束，DX为2
FINum10 PROC
    PUSH CX
    PUSH AX
    MOV CX,4
    MOV BX,0
    MOV DL,10
    MOV DH,0
NUM10LOOP:
    MOV AH,01H
    INT 21H
    CMP AL,'-'
    JZ F_NEGNUM                 ;负数出现    
    CMP AL,' '
    JZ F_SPACEEXIT              ;空格结束
    CMP AL,13
    JZ F_CHANGELINEEXIT         ;回车结束
    SUB AL,30H
    JB F_WRONGINPUT             ;错误的输入
    CMP AL,9
    JA F_WRONGINPUT             ;错误的输入
    CBW
    XCHG AX,BX
    MUL DL
    XCHG AX,BX
    ADD BX,AX
F_NEGNUM_END:
    LOOP NUM10LOOP
    JMP F_MAXNUMEXIT        ;最大数据
F_NEGNUM:
    CMP DH,1
    JZ F_WRONGINPUT
    MOV DH,1
    INC CX
    JMP F_NEGNUM_END
F_WRONGINPUT:
    MOV BX,0
    MOV DX,0
    JMP F_INNUMEND
F_MAXNUMEXIT:
    MOV DL,' '
    MOV AH,02H
    INT 21H
F_SPACEEXIT:
    MOV DL,1
    JMP F_NUMNEGJUDEG
F_CHANGELINEEXIT:  
    MOV DL,2
F_NUMNEGJUDEG:
    CMP DH,0
    JZ F_INNUMEND
    NEG BX
    MOV DH,0
F_INNUMEND: 
    POP AX
    POP CX
    RET
FINum10 ENDP
;[F]回车结束输入字符串，约定BX为地址，DX为数据最大的长度,在输入结束后自动添加$,注$占一个字符位
FIString_CGLIne PROC
    PUSH CX
    PUSH AX
    PUSH SI
    MOV CX,DX
    DEC CX
    MOV SI,0
InStrCGLoop:
    MOV AH,01H
    INT 21H
    CMP AL,13
    JZ FIStringCGEnd
    MOV [BX][SI],AL
    INC SI
    LOOP InStrCGLoop
FIStringCGEnd:
    MOV [BX][SI],'$'
    POP SI
    POP AX
    POP CX
    RET
FIString_CGLIne ENDP
;[F]定长输入字符串，约定BX为地址，DX为数据的长度,在输入结束后自动添加$
FIString PROC
    PUSH CX
    PUSH AX
    PUSH SI
    MOV CX,DX
    MOV SI,0
InStrLoop:
    MOV AH,01H
    INT 21H
    MOV [BX][SI],AL
    INC SI
    LOOP InStrLoop
FIStringEnd:
    MOV [BX][SI],'$'
    POP SI
    POP AX
    POP CX
    RET
FIString ENDP
;[F]输出学生信息,约定BX为学生信息存储地址
FOStudentInfo PROC
    PUSH AX
    PUSH DX
    PUSH CX
    PUSH SI
;---------------------------------------
    PUSH BX
        LEA BX,sPrintStuID
        CALL FOMSG
    POP BX
    LEA DX,[BX].studentId               ;输出学生ID
    XCHG DX,BX
    CALL FOMSG
    CALl FOChangeLine
    XCHG DX,BX
;---------------------------------------
    PUSH BX
        LEA BX,sPrintStuName
        CALL FOMSG
    POP BX
    LEA DX,[BX].studentName             ;输出学生姓名
    XCHG DX,BX
    CALL FOMSG
    CALl FOChangeLine
    XCHG DX,BX
;---------------------------------------
    PUSH BX
        LEA BX,sPrintStuSCore
        CALL FOMSG
    POP BX
    MOV CX,subjectNum                   ;输出学生的成绩
    MOV SI,0
scoreOutLoop:
    MOV AX,[BX].score[SI]
    MOV DX,BX
    MOV BX,AX
    CALL FONum10
    MOV BX,' '
    CALL FOChar
    MOV BX,DX
    INC SI
    INC SI
    LOOP scoreOutLoop
;---------------------------------------
    PUSH BX
        MOV BX,' '
        CALL FOCHAR
    POP BX
    MOV AX,[BX].totalSCore              ;输出学生的总成绩
    MOV DX,BX
    MOV BX,AX
    CALL FONum10
    CALL FOChangeLine
    MOV BX,DX
    POP SI
    POP CX
    POP DX
    POP AX
    RET
FOStudentInfo ENDP
;[F]字符串信息的输出，约定BX为信息的首地址存储地址
FOMSG PROC
    PUSH AX
    PUSH DX
    MOV DX,BX
    MOV AH,09H
    INT 21H
    POP DX
    POP AX
    RET
FOMSG ENDP
;[F]十进制的输出，约定BX为待输出数据的存储地址,注：鉴于不可抗因素最数据在-1000~+1000范围内
FONum10 PROC
    PUSH AX
    PUSH DX
    PUSH CX
    ADD BX,0
    JNS posNumPrint
    MOV DL,'-'
    MOV AH,02H
    INT 21H
    NEG BX
posNumPrint:
    MOV DX,0
    MOV DH,0
    MOV AX,BX
    MOV CL,10
sperateNumLoop:
    DIV CL
    MOV DL,AH
    ADD DL,'0'
    PUSH DX
    ADD DH,1
    CBW
    CMP AX,0
    JNZ sperateNumLoop
    MOV CL,DH
    MOV CH,0
printNum:
    POP DX
    MOV DH,0
    MOV AH,02H
    INT 21H
    LOOP printNum
    POP CX
    POP DX
    POP AX
    RET
FONum10 ENDP
;[F]输出一个字符，约定BX为存储地点，需要处理好后
FOChar PROC
    PUSH AX
    PUSH DX
    MOV DL,BL
    MOV AH,02H
    INT 21H
    POP DX
    POP AX
    RET
FOCHAR ENDP
;[F]换行
FOChangeLine PROC
    PUSH AX
    PUSH DX
    LEA DX,sChangeLine
    MOV AH,09H
    INT 21H
    POP DX
    POP AX
    RET
FOChangeLine ENDP
;[F]输出所有学生信息
FOStuInfoAll PROC
    PUSH CX
    PUSH BX
    PUSH AX
    LEA BX,class.studentId
    MOV CX,studentNum
stuInfoOutLoop:
    CALL FOStudentInfo
    ADD BX,studentSpace
    LOOP stuInfoOutLoop
    POP AX
    POP BX
    POP CX
    RET
FOStuInfoAll ENDP
;[F]输出所有学生信息BY成绩顺序,约定BX为地址的首地址
FOStuInfoBySCore PROC
    PUSH CX
    PUSH AX
    PUSH DX
    MOV CX,studentNum
stuInfoBySCoreOutLoop:
    PUSH BX
    MOV DX,[BX]
    MOV BX,DX
    CALL FOStudentInfo
    POP BX
    ADD BX,2
    LOOP stuInfoBySCoreOutLoop
    POP DX
    POP AX
    POP CX
    RET
FOStuInfoBySCore ENDP
;[F]输出数字,约定BX为输出的数的存储寄存器
F_O_NUM PROC
    PUSH CX
    PUSH DX
    MOV CX,4
F_NUM_LOOP_OUTONE:
    PUSH CX
    MOV CL,4
    ROL BX,CL
    MOV DL,BL
    AND DL,0FH
    CMP DL,9
    JBE F_NONEEDADDTOSHOWABC
    ADD DL,7H
F_NONEEDADDTOSHOWABC:
    ADD DL,30H
    MOV AH,02H
    INT 21H
    POP CX
    LOOP F_NUM_LOOP_OUTONE
    POP DX
    POP CX
    RET
F_O_NUM ENDP  
;[F]输出分段
FORangeOfSCore PROC
    PUSH BX
    PUSH AX
;----------------------------------输出0-60
    LEA BX,sPrintZeTOSix
    CALL FOMSG
    MOV BX,ZEROTOSIX
    CALL FONum10
    CALL FOChangeLine
;----------------------------------输出60-70
    LEA BX,sPrintSixTOSev
    CALL FOMSG
    MOV BX,SIXTOSEV
    CALL FONum10
    CALL FOChangeLine
;----------------------------------输出70-80
    LEA BX,sPrintSevTOEig
    CALL FOMSG
    MOV BX,SEVTOEIG
    CALL FONum10
    CALL FOChangeLine
;----------------------------------输出80-90
    LEA BX,sPrintEIGTOSix
    CALL FOMSG
    MOV BX,EIGTONIN
    CALL FONum10
    CALL FOChangeLine
;----------------------------------输出90
    LEA BX,sPrintNinAbove
    CALL FOMSG
    MOV BX,NINTOONE
    CALL FONum10
    CALL FOChangeLine

    POP AX
    POP BX
    RET
FORangeOfSCore ENDP

CODES ENDS
    END START
