Imports System.ComponentModel
Imports SIL3.LDLL178__COMMON_CODE__MICRO_TMER
''' <summary>
''' Basic framework for rLoop Flight Control Emulation
''' Lachlan Grogan - SafetyLok
''' </summary>
Public Class Form1

#Region "CONSTANTS"

    ''' <summary>
    ''' SC16 UARTS
    ''' </summary>
    Private Const C_NUM__SC16IS As Integer = 8

    ''' <summary>
    ''' Number of ASI controllers
    ''' </summary>
    Private Const C_NUM__ASI As Integer = 8

#End Region '#Region "CONSTANTS"

#Region "DLL HANDLING"



    ''' <summary>
    ''' The name of our DLL, could be a bit better done with relative paths
    ''' </summary>
    Private Const C_DLL_NAME As String = "..\..\..\PROJECT_CODE\DLLS\LDLL174__RLOOP__LCCM655\bin\Debug\LDLL174__RLOOP__LCCM655.dll"

#Region "WIN32 KERNEL"
    Private Declare Auto Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (ByVal pDst() As UInt16, ByVal pSrc As IntPtr, ByVal ByteLen As UInt32)
    Private Declare Auto Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (ByVal pDst() As Byte, ByVal pSrc As IntPtr, ByVal ByteLen As UInt32)
#End Region '#Region "WIN32 KERNEL"

#Region "WIN32/DEBUG"
    ''' <summary>
    ''' The delegate sub for win32 debug (text) c
    ''' </summary>
    ''' <param name="pu8String"></param>
    ''' <remarks></remarks>
    <System.Runtime.InteropServices.UnmanagedFunctionPointerAttribute(System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Public Delegate Sub DEBUG_PRINTF__CallbackDelegate(ByVal pu8String As IntPtr)


    ''' <summary>
    ''' The debugger callback
    ''' </summary>
    ''' <param name="callback"></param>
    ''' <remarks></remarks>
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vDEBUG_PRINTF_WIN32__Set_Callback(ByVal callback As MulticastDelegate)
    End Sub


    'Ethernet
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Public Shared Sub vETH_WIN32__Set_Ethernet_TxCallback(ByVal callback As MulticastDelegate)
    End Sub
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Public Shared Sub vETH_WIN32__Ethernet_Input(pu8Buffer() As Byte, u16BufferLength As UInt16)
    End Sub
    <System.Runtime.InteropServices.UnmanagedFunctionPointerAttribute(System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Public Delegate Sub ETH_WIN32__TxCallbackDelegate(ByVal pu8Buffer As IntPtr, ByVal u16BufferLength As UInt16)


    'mma8451
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Public Shared Sub vMMA8451_WIN32__Set_ReadDataCallback(ByVal callback As MulticastDelegate)
    End Sub
    <System.Runtime.InteropServices.UnmanagedFunctionPointerAttribute(System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Public Delegate Sub MMA8451_WIN32__ReadDataCallbackDelegate(u8DeviceIndex As Byte, pu8X As IntPtr, pu8Y As IntPtr, pu8Z As IntPtr)
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Public Shared Sub vMMA8451_WIN32__TriggerInterrupt(u8DeviceIndex As Byte)
    End Sub

    'stepper system
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Public Shared Sub vSTEPDRIVE_WIN32__Set_UpdatePositionCallback(ByVal callback As MulticastDelegate)
    End Sub
    <System.Runtime.InteropServices.UnmanagedFunctionPointerAttribute(System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Public Delegate Sub STEPDRIVE_WIN32__Set_UpdatePositionCallbackDelegate(u8MotorIndex As Byte, u8Step As Byte, u8Dir As Byte, s32Position As Int32)
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Public Shared Sub vSTEPDRIVE_WIN32__ForcePosition(u8MotorIndex As Byte, s32Position As Int32)
    End Sub


    'SC16 UARTS
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Public Shared Sub vSC16IS_WIN32__Set_TxData_Callback(u8DeviceIndex As Byte, ByVal callback As MulticastDelegate)
    End Sub
    <System.Runtime.InteropServices.UnmanagedFunctionPointerAttribute(System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Public Delegate Sub SC16IS_WIN32__Set_TxData_CallbackDelegate(u8DeviceIndex As Byte, pu8Data As IntPtr, u8Length As Byte)
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Public Shared Sub vSC16IS_WIN32__InjectData(u8DeviceIndex As Byte, pu8Data() As Byte, u8Length As Byte)
    End Sub

    'AMC7812 for HE Thrott
    <System.Runtime.InteropServices.UnmanagedFunctionPointerAttribute(System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Public Delegate Sub AMC7812_WIN32__Set_DACVoltsCallbackDelegate(u8Channel As Byte, f32Volts As Single)
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Public Shared Sub vAMC7812_WIN32__Set_DACVoltsCallback(ByVal callback As MulticastDelegate)
    End Sub


#End Region '#Region "WIN32/DEBUG"

#Region "C CODE SPECIFICS"

    ''' <summary>
    ''' The Init function from the power node
    ''' </summary>
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vFCU__Init()
    End Sub

    ''' <summary>
    ''' the process function from the power node
    ''' </summary>
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vFCU__Process()
    End Sub


    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vFCU__RTI_10MS_ISR()
    End Sub
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vFCU__RTI_100MS_ISR()
    End Sub
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vSTEPDRIVE_TIMEBASE__ISR()
    End Sub


    'Laser Distance
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vFCU_LASERDIST_WIN32__Set_DistanceRaw(f32Value As Single)
    End Sub

    'laser optoncdt
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vFCU_LASEROPTO_WIN32__Set_DistanceRaw(u32Index As UInt32, f32Value As Single)
    End Sub

    'brake switches
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vFCU_BRAKES_SW_WIN32__Inject_SwitchState(u8Brake As Byte, u8ExtendRetract As Byte, u8Value As Byte)
    End Sub
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vFCU_BRAKES_SW__Left_SwitchExtend_ISR()
    End Sub
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vFCU_BRAKES_SW__Left_SwitchRetract_ISR()
    End Sub
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vFCU_BRAKES_SW__Right_SwitchExtend_ISR()
    End Sub
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vFCU_BRAKES_SW__Right_SwitchRetract_ISR()
    End Sub

    'MLP
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vFCU_BRAKES_MLP_WIN32__ForceADC(u8Brake As Byte, u16Value As UInt16)
    End Sub

    'ASI
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Function u8FCU_ASI_MUX_WIN32__Get() As Byte
    End Function
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Function u16FCU_ASI_CRC__ComputeCRC(pu8Data() As Byte, u16DataLen As UInt16) As UInt16
    End Function

    'Testing Area
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vLCCM655R0_TS_000()
    End Sub
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vLCCM655R0_TS_001()
    End Sub
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vLCCM655R0_TS_002()
    End Sub
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vLCCM655R0_TS_003()
    End Sub
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vLCCM655R0_TS_004()
    End Sub
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vLCCM655R0_TS_005()
    End Sub
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vLCCM655R0_TS_006()
    End Sub



#End Region '#Region "C CODE SPECIFICS"

#End Region '#Region "DLL HANDLING"

#Region "MEMBERS"


    ''' <summary>
    ''' A list of ASI controllers
    ''' </summary>
    Private m_pASI() As ASIController

    ''' <summary>
    ''' Our output text box used for serial debugging
    ''' </summary>
    ''' <remarks></remarks>
    Private m_txtOutput As Windows.Forms.TextBox


    Private m_txtLaserDist__ValueRaw As TextBox

    Private m_txtLaserOpto() As TextBox

    ''' <summary>
    ''' The debug delegate
    ''' </summary>
    ''' <remarks></remarks>
    Private m_pDebug_Delegate As DEBUG_PRINTF__CallbackDelegate

    'ETH
    Private m_pETH_TX__Delegate As ETH_WIN32__TxCallbackDelegate

    ''' <summary>
    ''' When the MMA8451 wants data from us
    ''' </summary>
    Private m_pMMA8451_ReadData__Delegate As MMA8451_WIN32__ReadDataCallbackDelegate


    Private m_pStepDrive_UpdatePos__Delegate As STEPDRIVE_WIN32__Set_UpdatePositionCallbackDelegate

    ''' <summary>
    ''' When the SC16 subsystem wants to transmit
    ''' </summary>
    Private m_pSC16_TxData__Delegate As SC16IS_WIN32__Set_TxData_CallbackDelegate

    ''' <summary>
    ''' When the DAC voltage is updated.
    ''' </summary>
    Private m_pAMC7812_DACVolts__Delegate As AMC7812_WIN32__Set_DACVoltsCallbackDelegate

    ''' <summary>
    ''' The thread to run our DLL in
    ''' </summary>
    ''' <remarks></remarks>
    Private m_pMainThread As Threading.Thread

    ''' <summary>
    ''' Global flag to indicate the thread is running
    ''' </summary>
    Private m_bThreadRun As Boolean

    Private m_pSafeUDP As SIL3.SafeUDP.StdUDPLayer

    'Private m_pTimer50u As System.Timers.Timer
    Private m_pTimer10m As System.Timers.Timer
    Private m_pTimer100m As System.Timers.Timer
    Private m_pTimer50u As MicroTimer
    'Private m_pTimer10m As MicroTimer
    'Private m_pTimer100m As MicroTimer



    ''' <summary>
    ''' Timer to handle accels.
    ''' </summary>
    Private m_pTimerAccel As System.Timers.Timer

    Private m_txtBrakeL_Pos As TextBox
    Private m_txtBrakeR_Pos As TextBox
    Private m_txtASI_Volts() As TextBox

#Region "SENSOR SIM VALUES"

    Private m_iAccel0_X As Integer
    Private m_iAccel0_Y As Integer
    Private m_iAccel0_Z As Integer

    Private m_iL_MLP As Integer
    Private m_iR_MLP As Integer

#End Region '#Region "SENSOR SIM VALUES"

#End Region '#Region "MEMBERS"

#Region "FORM LAYOUT"

    ''' <summary>
    ''' Create the form
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles Me.Load

        'setup our form text and size
        Me.Text = "rLoop Flight Control Unit Emulator (Build: " & My.Application.Info.Version.ToString & ")"
        Me.BackColor = System.Drawing.Color.White
        Me.WindowState = FormWindowState.Maximized

        'create a panel inside our form which is easy to add stuff to
        Dim pP As New Panel
        With pP
            .BackColor = System.Drawing.Color.White
            .Dock = DockStyle.Fill
        End With
        Me.Controls.Add(pP)

        'add a start / stop button
        Dim pB1 As New Button
        With pB1
            .Location = New Point(10, 10)
            .Size = New Size(100, 24)
            .Text = "Start"
        End With
        pP.Controls.Add(pB1)
        AddHandler pB1.Click, AddressOf Me.btnStart__Click


        Dim pB2 As New Button
        With pB2
            .Location = New Point(pB1.Location.X + pB1.Size.Width + 5, 10)
            .Size = New Size(100, 24)
            .Text = "Test Cases"
        End With
        pP.Controls.Add(pB2)
        AddHandler pB2.Click, AddressOf Me.btnTestCases__Click

        'this area is going to get very messy due to absense of SIL3 libs.

        'create some input item.
        Dim l1 As New Label
        With l1
            .Location = New Point(10, pB1.Top + pB1.Height + 20)
            .Text = "LaserDist - RAW"
        End With
        pP.Controls.Add(l1)
        Me.m_txtLaserDist__ValueRaw = New TextBox
        With Me.m_txtLaserDist__ValueRaw
            .Location = New Point(10, l1.Top + l1.Height + 0)
            .Size = New Size(100, 24)
            .Text = "0.0"
        End With
        pP.Controls.Add(Me.m_txtLaserDist__ValueRaw)
        AddHandler Me.m_txtLaserDist__ValueRaw.KeyDown, AddressOf Me.txtLaserDistanceRaw__KeyDown


        Dim l2(6 - 1) As Label
        ReDim Me.m_txtLaserOpto(6 - 1)
        For iCounter As Integer = 0 To 6 - 1
            If iCounter = 0 Then
                l2(iCounter) = New Label
                With l2(iCounter)
                    .Location = New Point(10, Me.m_txtLaserDist__ValueRaw.Top + pB1.Height + 20)
                    .Text = "OptoNCDT:" & iCounter.ToString & " - RAW"
                    .AutoSize = True
                End With
            Else
                l2(iCounter) = New Label
                With l2(iCounter)
                    .Location = New Point(Me.m_txtLaserOpto(iCounter - 1).Left + Me.m_txtLaserOpto(iCounter - 1).Width + 20, l2(iCounter - 1).Top)
                    .Text = "OptoNCDT:" & iCounter.ToString & " - RAW"
                    .AutoSize = True
                End With
            End If
            pP.Controls.Add(l2(iCounter))

            Me.m_txtLaserOpto(iCounter) = New TextBox
            With Me.m_txtLaserOpto(iCounter)
                .Location = New Point(l2(iCounter).Left, l2(iCounter).Top + l2(iCounter).Height + 0)
                .Size = New Size(100, 24)
                .Text = "0.0"
                .Tag = iCounter.ToString
            End With
            pP.Controls.Add(Me.m_txtLaserOpto(iCounter))
            AddHandler Me.m_txtLaserOpto(iCounter).KeyDown, AddressOf Me.txtLaserOptoRaw__KeyDown

        Next ' For iCounter As Integer = 0 To 6 - 1


        Dim l3 As New Label
        With l3
            .Location = New Point(10, Me.m_txtLaserOpto(0).Top + Me.m_txtLaserOpto(0).Height + 20)
            .Text = "Brake L Pos"
        End With
        pP.Controls.Add(l3)
        Me.m_txtBrakeL_Pos = New TextBox
        With Me.m_txtBrakeL_Pos
            .Location = New Point(10, l3.Top + l3.Height + 0)
            .Size = New Size(100, 24)
            .Text = "0.0"
        End With
        pP.Controls.Add(Me.m_txtBrakeL_Pos)

        Dim l4 As New Label
        With l4
            .Location = New Point(Me.m_txtBrakeL_Pos.Left + Me.m_txtBrakeL_Pos.Width + 20, l3.Top)
            .Text = "Brake R Pos"
        End With
        pP.Controls.Add(l4)
        Me.m_txtBrakeR_Pos = New TextBox
        With Me.m_txtBrakeR_Pos
            .Location = New Point(l4.Left, l4.Top + l4.Height + 0)
            .Size = New Size(100, 24)
            .Text = "0.0"
        End With
        pP.Controls.Add(Me.m_txtBrakeR_Pos)


        Dim l5(C_NUM__ASI - 1) As Label
        ReDim Me.m_txtASI_Volts(C_NUM__ASI - 1)
        For iCounter As Integer = 0 To 6 - 1
            If iCounter = 0 Then
                l5(iCounter) = New Label
                With l5(iCounter)
                    .Location = New Point(10, Me.m_txtBrakeL_Pos.Top + pB1.Height + 20)
                    .Text = "ASI:" & iCounter.ToString & " - Volts"
                    .AutoSize = True
                End With
            Else
                l5(iCounter) = New Label
                With l5(iCounter)
                    .Location = New Point(Me.m_txtASI_Volts(iCounter - 1).Left + Me.m_txtASI_Volts(iCounter - 1).Width + 20, l5(iCounter - 1).Top)
                    .Text = "ASI:" & iCounter.ToString & " - Volts"
                    .AutoSize = True
                End With
            End If
            pP.Controls.Add(l5(iCounter))

            Me.m_txtASI_Volts(iCounter) = New TextBox
            With Me.m_txtASI_Volts(iCounter)
                .Location = New Point(l5(iCounter).Left, l5(iCounter).Top + l5(iCounter).Height + 0)
                .Size = New Size(100, 24)
                .Text = "0.0"
                .Tag = iCounter.ToString
            End With
            pP.Controls.Add(Me.m_txtASI_Volts(iCounter))

        Next ' For iCounter As Integer = 0 To 6 - 1



        'create a logging box
        Me.m_txtOutput = New TextBox
        With Me.m_txtOutput
            .Multiline = True
            .Size = New Size(100, 300)
            .ScrollBars = ScrollBars.Both
            .Dock = DockStyle.Bottom
            .BorderStyle = BorderStyle.FixedSingle
        End With
        pP.Controls.Add(Me.m_txtOutput)

        'call the system setup
        Me.Setup_System()

    End Sub

    ''' <summary>
    ''' Handles an intentional shutdown
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    Private Sub Form1_Closing(sender As Object, e As CancelEventArgs) Handles Me.Closing

        'kill the threads
        Me.m_pMainThread.Abort()

        Me.m_pTimer10m.Stop()
        Me.m_pTimer100m.Stop()

        If Not Me.m_pSafeUDP Is Nothing Then
            Me.m_pSafeUDP.Destroy()
        End If

    End Sub


#End Region '#Region "FORM LAYOUT"

#Region "SYSTEM INIT"
    ''' <summary>
    ''' Setup anyting else on the system
    ''' </summary>
    Private Sub Setup_System()

        'create our ASI's
        ReDim Me.m_pASI(C_NUM__ASI)
        For iCounter As Integer = 0 To C_NUM__ASI - 1
            Me.m_pASI(iCounter) = New ASIController()
            AddHandler Me.m_pASI(iCounter).Tx_RS485, AddressOf Me.ASI_Tx_RS485
        Next


        Me.m_pSafeUDP = New SIL3.SafeUDP.StdUDPLayer("127.0.0.1", 9100, "FCU_ETH_EMU", True, True)
        AddHandler Me.m_pSafeUDP.UserEvent__UDPSafe__RxPacket, AddressOf Me.InernalEvent__UDPSafe__RxPacket
        AddHandler Me.m_pSafeUDP.UserEvent__NewPacket, AddressOf Me.InternalEvent__NewPacket

        'Seup the debugging support if needed
        Me.m_pDebug_Delegate = AddressOf Me.DEBUG_PRINTF_WIN32_Callback
        vDEBUG_PRINTF_WIN32__Set_Callback(Me.m_pDebug_Delegate)

        'setup other callbacks

        Me.m_pETH_TX__Delegate = AddressOf Me.ETH_WIN32__TxCallback_Sub
        vETH_WIN32__Set_Ethernet_TxCallback(Me.m_pETH_TX__Delegate)

        Me.m_pMMA8451_ReadData__Delegate = AddressOf Me.MMA8451_WIN32__ReadDataCallback_Sub
        vMMA8451_WIN32__Set_ReadDataCallback(Me.m_pMMA8451_ReadData__Delegate)

        Me.m_pStepDrive_UpdatePos__Delegate = AddressOf Me.STEPDRIVE_WIN32__UpdatePostion
        vSTEPDRIVE_WIN32__Set_UpdatePositionCallback(Me.m_pStepDrive_UpdatePos__Delegate)

        Me.m_pSC16_TxData__Delegate = AddressOf SC16IS_WIN32__TxData
        For iCounter As Integer = 0 To C_NUM__SC16IS - 1
            vSC16IS_WIN32__Set_TxData_Callback(iCounter, Me.m_pSC16_TxData__Delegate)
        Next

        Me.m_pAMC7812_DACVolts__Delegate = AddressOf Me.AMC7182_DAC__SetVolts
        vAMC7812_WIN32__Set_DACVoltsCallback(Me.m_pAMC7812_DACVolts__Delegate)

        'do the threading
        Me.m_pMainThread = New Threading.Thread(AddressOf Me.Thread__Main)
        Me.m_pMainThread.Name = "FCU THREAD"

        'stimers
        Timers__Setup()

    End Sub
#End Region '#Region "SYSTEM INIT"

#Region "KEY PRESS HANDLERS"

    Private Sub txtLaserOptoRaw__KeyDown(s As Object, e As KeyEventArgs)

        'get our type
        Dim pT As TextBox = CType(s, TextBox)
        Dim iIndex As Integer = CInt(pT.Tag)

        'handle enter key
        If e.KeyCode = Keys.Enter Then
            'check safety
            If Me.m_bThreadRun = False Then
                MsgBox("Warn: You must have thread running.")
            Else
                'convert string to float32 (single on WIN32)
                Dim sValue As Single = Single.Parse(Me.m_txtLaserOpto(iIndex).Text)

                'update the DLL
                vFCU_LASEROPTO_WIN32__Set_DistanceRaw(iIndex, sValue)

            End If
        End If

    End Sub

    Private Sub txtLaserDistanceRaw__KeyDown(s As Object, e As KeyEventArgs)
        'handle enter key
        If e.KeyCode = Keys.Enter Then
            'check safety
            If Me.m_bThreadRun = False Then
                MsgBox("Warn: You must have thread running.")
            Else
                'convert string to float32 (single on WIN32)
                Dim sValue As Single = Single.Parse(Me.m_txtLaserDist__ValueRaw.Text)

                'update the DLL
                vFCU_LASERDIST_WIN32__Set_DistanceRaw(sValue)

            End If
        End If
    End Sub
#End Region '#Region "KEY PRESS HANDLERS"

#Region "BUTTON HANDLERS"

    ''' <summary>
    ''' Run the test cases
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    Private Sub btnTestCases__Click(sender As Object, e As EventArgs)

        'brakes
        'vLCCM655R0_TS_000()

        'track contrast database
        'vLCCM655R0_TS_001()
        vLCCM655R0_TS_003()

        'brake lookup
        'vLCCM655R0_TS_006()
    End Sub

    ''' <summary>
    ''' Called to start/stop
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    Private Sub btnStart__Click(sender As Object, e As EventArgs)

        'get the object
        Dim pB As Button = CType(sender, Button)

        If pB.Text = "Start" Then

            'setup the default values
            Me.m_iAccel0_X = -100
            Me.m_iAccel0_Y = 500
            Me.m_iAccel0_Z = 1024


            'set the flag
            Me.m_bThreadRun = True

            'set the new text
            pB.Text = "Stop"

            'start the thread
            Me.m_pMainThread.Start()

        Else
            'clear the flag
            Me.m_bThreadRun = False

            'stop threading
            Me.m_pMainThread.Abort()

            'reset the text
            pB.Text = "Start"

        End If

    End Sub

#End Region '#Region "BUTTON HANDLERS"

#Region "ACCEL SIMULATION"

#End Region '#Region "ACCEL SIMULATION"

#Region "THREADING"
    ''' <summary>
    ''' This is the same as Main() in C
    ''' </summary>
    Private Sub Thread__Main()

        'call Init
        vFCU__Init()

        'needs to be done due to WIN32_ETH_Init
        vETH_WIN32__Set_Ethernet_TxCallback(Me.m_pETH_TX__Delegate)




        'force the two motor positions to random so as we can simulate the cal process
        vSTEPDRIVE_WIN32__ForcePosition(0, -34)
        vSTEPDRIVE_WIN32__ForcePosition(1, 175)

        vFCU_BRAKES_MLP_WIN32__ForceADC(0, 0)
        vFCU_BRAKES_MLP_WIN32__ForceADC(1, 0)

        'config the brake switches into some state
        For iBrake As Integer = 0 To 2 - 1
            For iSwitch As Integer = 0 To 2 - 1
                vFCU_BRAKES_SW_WIN32__Inject_SwitchState(iBrake, iSwitch, 0)
            Next
        Next

        'stay here until thread abort
        While True

            'add here any things that need updating like pod sensor data

            'call process
            Try
                vFCU__Process()

            Catch ex As Exception
                Console.Write(ex.ToString)
            End Try

            'just wait a little bit
            Threading.Thread.Sleep(1)
        End While
    End Sub

#End Region '#Region "THREADING"

#Region "TIMERS"
    ''' <summary>
    ''' Start the timers.
    ''' </summary>
    Private Sub Timers__Setup()

        'needed for stepper drive
        'Me.m_pTimer50u = New System.Timers.Timer
        'Me.m_pTimer50u.Interval = 2
        'AddHandler Me.m_pTimer50u.Elapsed, AddressOf Me.Timers__T50u_Tick
        'Me.m_pTimer50u.Start()

        Me.m_pTimer10m = New System.Timers.Timer
        Me.m_pTimer10m.Interval = 10
        AddHandler Me.m_pTimer10m.Elapsed, AddressOf Me.Timers__T10_Tick
        Me.m_pTimer10m.Start()

        Me.m_pTimer100m = New System.Timers.Timer
        Me.m_pTimer100m.Interval = 100
        AddHandler Me.m_pTimer100m.Elapsed, AddressOf Me.Timers__T100_Tick
        Me.m_pTimer100m.Start()

        Me.m_pTimer50u = New MicroTimer
        Me.m_pTimer50u.Interval = 500
        AddHandler Me.m_pTimer50u.MicroTimerElapsed, AddressOf Me.Timers__T50u_Tick
        Me.m_pTimer50u.Start()

        'Me.m_pTimer10m = New MicroTimer
        'Me.m_pTimer10m.Interval = 10 * 1000
        'AddHandler Me.m_pTimer10m.MicroTimerElapsed, AddressOf Me.Timers__T10_Tick
        'Me.m_pTimer10m.Start()

        'Me.m_pTimer100m = New MicroTimer
        'Me.m_pTimer100m.Interval = 100 * 1000
        'AddHandler Me.m_pTimer100m.MicroTimerElapsed, AddressOf Me.Timers__T100_Tick
        'Me.m_pTimer100m.Start()

        '100hz
        Me.m_pTimerAccel = New System.Timers.Timer
        Me.m_pTimerAccel.Interval = 100
        AddHandler Me.m_pTimerAccel.Elapsed, AddressOf Me.Timers__Accel_Tick
        Me.m_pTimerAccel.Start()

    End Sub

    ''' <summary>
    ''' 50us timer
    ''' </summary>
    ''' <param name="s"></param>
    ''' <param name="e"></param>
    Private Sub Timers__T50u_Tick(s As Object, e As MicroTimerEventArgs) 'System.Timers.ElapsedEventArgs)
        If Me.m_bThreadRun = True Then
            vSTEPDRIVE_TIMEBASE__ISR()
        End If
    End Sub

    ''' <summary>
    ''' 10ms timer
    ''' </summary>
    ''' <param name="s"></param>
    ''' <param name="e"></param>
    Private Sub Timers__T10_Tick(s As Object, e As System.Timers.ElapsedEventArgs)
        If Me.m_bThreadRun = True Then
            vFCU__RTI_10MS_ISR()
        End If
    End Sub

    ''' <summary>
    ''' 100ms timer
    ''' </summary>
    ''' <param name="s"></param>
    ''' <param name="e"></param>
    Private Sub Timers__T100_Tick(s As Object, e As System.Timers.ElapsedEventArgs)
        If Me.m_bThreadRun = True Then
            vFCU__RTI_100MS_ISR()
        End If
    End Sub


    ''' <summary>
    ''' 100ms timer
    ''' </summary>
    ''' <param name="s"></param>
    ''' <param name="e"></param>
    Private Sub Timers__Accel_Tick(s As Object, e As System.Timers.ElapsedEventArgs)
        If Me.m_bThreadRun = True Then
            vMMA8451_WIN32__TriggerInterrupt(0)
            vMMA8451_WIN32__TriggerInterrupt(1)
        End If
    End Sub

#End Region '#Region "TIMERS"

#Region "TEXT DEBUG"

    ''' <summary>
    ''' Called when the debug layer wants to print a string
    ''' </summary>
    ''' <param name="pu8String"></param>
    ''' <remarks></remarks>
    Private Sub DEBUG_PRINTF_WIN32_Callback(ByVal pu8String As IntPtr)

        Dim bArray() As Byte

        'max text size
        Dim iMaxArray As Integer = 128

        'update the array
        ReDim bArray(iMaxArray - 1)

        'copy 128 bytes of memory, does not matter if we copy more than is needed
        CopyMemory(bArray, pu8String, UInt32.Parse(128))

        'determine the string length
        Dim iLen As Integer = 0
        For iCounter As Integer = 0 To iMaxArray - 1
            If bArray(iCounter) = &H0 Then
                iLen = iCounter
                Exit For
            End If
        Next

        'copy the string
        'Console.WriteLine(Convert_ByteArrayASCII_ToString(bArray, iLen, 0))
        Me.Threadsafe__AppendText(Me.m_txtOutput, Convert_ByteArrayASCII_ToString(bArray, iLen, 0) & Environment.NewLine)
    End Sub

    ''' <summary>
    ''' Helper function to convert a byte array into a string.
    ''' </summary>
    ''' <param name="pByteArray"></param>
    ''' <param name="iArrayLength"></param>
    ''' <param name="iStartPos"></param>
    ''' <returns></returns>
    Private Function Convert_ByteArrayASCII_ToString(ByVal pByteArray() As Byte, ByVal iArrayLength As Integer, Optional ByVal iStartPos As Integer = 0) As String
        Dim pSB As New System.Text.StringBuilder
        Dim iCounter As Integer

        'go through the string
        For iCounter = 0 To iArrayLength - 1
            'get the byte
            Dim pu8 As Byte = pByteArray(iStartPos + iCounter)
            'convert to ascii

            'conver to ascii
            Dim pE As New System.Text.ASCIIEncoding
            Dim bByteArray(2) As Byte
            Dim cTemp(2) As Char
            bByteArray(0) = pu8
            'convert
            cTemp = pE.GetChars(bByteArray, 0, 1)

            Dim c2 As Char = cTemp(0)
            If c2 = Microsoft.VisualBasic.ChrW(&H0) Then
                Return pSB.ToString
            End If
            pSB.Append(c2)
        Next

        Return pSB.ToString
    End Function

#End Region '#Region "TEXT DEBUG"

#Region "THREAD SAFETY"

    'make some delegates
    Private Delegate Sub SetTextCallback(ByRef pT As TextBox, ByVal sData As String)
    Private Delegate Sub AppendTextCallback(ByRef pT As TextBox, ByVal sData As String)

    ''' <summary>
    ''' Sets text on the control in a threasafe mannor
    ''' </summary>
    ''' <param name="sData">The string to set</param>
    ''' <remarks></remarks>
    Public Sub Threadsafe__SetText(ByRef pT As TextBox, ByVal sData As String)

        'check invoke
        If MyBase.InvokeRequired = True Then
            'yep, make a new callback
            Dim d As New SetTextCallback(AddressOf Threadsafe__SetText)
            Try
                MyBase.Invoke(d, New Object() {pT, sData})
            Catch ex As Exception
                MsgBox(ex.ToString)
            End Try
        Else
            'we can just update
            pT.Text = sData
        End If
    End Sub

    ''' <summary>
    ''' Append text in a threadsafe mannor
    ''' </summary>
    ''' <param name="sData"></param>
    ''' <remarks></remarks>
    Public Sub Threadsafe__AppendText(ByRef pT As TextBox, ByVal sData As String)
        If MyBase.InvokeRequired Then
            Dim d As New AppendTextCallback(AddressOf Threadsafe__AppendText)
            Try
                MyBase.Invoke(d, New Object() {pT, sData})
            Catch ex As Exception
                MsgBox(ex.ToString)
            End Try
        Else
            pT.AppendText(sData)
        End If
    End Sub

#End Region '#Region "THREAD SAFETY"

#Region "ETH RX"

    ''' <summary>
    ''' Rx a new raw packet
    ''' </summary>
    ''' <param name="u8Array"></param>
    ''' <param name="iLength"></param>
    Public Sub InternalEvent__NewPacket(u8Array() As Byte, iLength As Integer)
        If Me.m_bThreadRun = True Then
            vETH_WIN32__Ethernet_Input(u8Array, iLength)
        End If
    End Sub


    ''' <summary>
    ''' RX a UDP safe packet and fake the eth-ii layer
    ''' </summary>
    ''' <param name="ePacketType"></param>
    ''' <param name="u16PayloadLength"></param>
    ''' <param name="u8Payload"></param>
    ''' <param name="u16CRC"></param>
    ''' <param name="bCRCOK"></param>
    ''' <param name="u32Seq"></param>
    Public Sub InernalEvent__UDPSafe__RxPacket(ByVal ePacketType As SIL3.SafeUDP.PacketTypes.SAFE_UDP__PACKET_T, ByVal u16PayloadLength As SIL3.Numerical.U16, ByRef u8Payload() As Byte, ByVal u16CRC As SIL3.Numerical.U16, ByVal bCRCOK As Boolean, ByVal u32Seq As UInt32)
        'MsgBox("packet")

        Dim u8Buff(1500) As Byte
        Return
        'Update the hardware
        If Me.m_bThreadRun = True Then

            'update the hardware
            'now let the fun begin, on loopback we have no eth2 layer

            'dest mac, source mac, 
            u8Buff(0) = 0
            u8Buff(1) = 0
            u8Buff(2) = 0
            u8Buff(3) = 0
            u8Buff(4) = 0
            u8Buff(5) = 0

            u8Buff(6) = 0
            u8Buff(7) = 0
            u8Buff(8) = 0
            u8Buff(9) = 0
            u8Buff(10) = 0
            u8Buff(11) = 0

            'ipv4 eth type
            u8Buff(12) = &H8
            u8Buff(13) = &H0

            For iCounter = 0 To u16PayloadLength.To__Uint16 - 1
                u8Buff(iCounter + 14) = u8Payload(iCounter)
            Next



            vETH_WIN32__Ethernet_Input(u8Buff, u16PayloadLength.To__Uint16 + 14)


        End If

    End Sub


    ''' <summary>
    ''' Called when teh DLL wants to trasmit eth data.
    ''' </summary>
    ''' <param name="u8Buffer"></param>
    ''' <param name="u16BufferLength"></param>
    ''' <remarks></remarks>
    Private Sub ETH_WIN32__TxCallback_Sub(ByVal u8Buffer As IntPtr, ByVal u16BufferLength As UInt16)

        Dim iEthPort As Integer = 9100
        Dim bArray(1500 - 1) As Byte
        SIL3.MemoryCopy.MemoryCopy.Copy_Memory(bArray, u8Buffer, CInt(u16BufferLength))


        'pass the packet off to our 802.3 layers
        Dim p802 As New SIL3.IEEE802_3.EthernetFrame(bArray, CInt(u16BufferLength), False)

        If p802.m_eEtherType = SIL3.IEEE802_3.EthernetFrame.eEtherType.Internet_Protocol_version_4 Then

            Dim p802_IPV4 As New SIL3.IEEE802_3.IPLayer.IPV4(p802.m_bPayload, p802.m_iPayloadLength)
            If p802_IPV4.m_pU8Protocol.To__Uint8 = &H11 Then

                Dim p802_UDP As New SIL3.IEEE802_3.UDP(p802_IPV4.m_bPayload, p802_IPV4.m_iPayloadLength)
                'If p802_UDP.m_pu16DestPort.To__Int = iEthPort Then

                'if we are here, we assume we are on loopback
                Dim pStdUDP As New SIL3.SafeUDP.StdUDPLayer("127.0.0.1", p802_UDP.m_pu16DestPort.To__Int) 'iEthPort)
                AddHandler pStdUDP.UserEvent__UDPSafe__RxPacket, AddressOf Me.UserEvent__UDPSafe__RxPacket

                'retransmit
                pStdUDP.UserEvent__NewUDP(p802_UDP, True)

                'End If

            End If

        End If


    End Sub

    Private Sub UserEvent__UDPSafe__RxPacket(ByVal ePacketType As SIL3.SafeUDP.PacketTypes.SAFE_UDP__PACKET_T, ByVal u16PayloadLength As SIL3.Numerical.U16, ByRef u8Payload() As Byte, ByVal u16CRC As SIL3.Numerical.U16, ByVal bCRC_OK As Boolean, ByVal u32Sequence As UInt32)


    End Sub


#End Region '#Region "ETH RX"

#Region "MMA8451"

    ''' <summary>
    ''' Callback when the MMA wants to read some new data
    ''' </summary>
    ''' <param name="u8DeviceIndex"></param>
    ''' <param name="ps16X"></param>
    ''' <param name="ps16Y"></param>
    ''' <param name="ps16Z"></param>
    Private Sub MMA8451_WIN32__ReadDataCallback_Sub(u8DeviceIndex As Byte, ps16X As IntPtr, ps16Y As IntPtr, ps16Z As IntPtr)

        Dim iEthPort As Integer = 9100
        Dim bArray(1500 - 1) As Byte
        'SIL3.MemoryCopy.MemoryCopy.Copy_Memory(bArray, u8Buffer, CInt(u16BufferLength))

        Dim xS16X As SIL3.Numerical.S16
        Dim xS16Y As SIL3.Numerical.S16
        Dim xS16Z As SIL3.Numerical.S16

        If u8DeviceIndex = 0 Then
            xS16X = New SIL3.Numerical.S16(Me.m_iAccel0_X)
            xS16Y = New SIL3.Numerical.S16(Me.m_iAccel0_Y)
            xS16Z = New SIL3.Numerical.S16(Me.m_iAccel0_Z)
        Else
            xS16X = New SIL3.Numerical.S16(0)
            xS16Y = New SIL3.Numerical.S16(2048)
            xS16Z = New SIL3.Numerical.S16(0)
        End If

        'this will result in an arith overflow if not careful.
        'Me.m_iAccel0_X += 1
        'Me.m_iAccel0_Y += 1
        'Me.m_iAccel0_Z += 1

        Dim bX(2 - 1) As Byte
        xS16X.To__Array(bX, 0)

        Dim bY(2 - 1) As Byte
        xS16Y.To__Array(bY, 0)

        Dim bZ(2 - 1) As Byte
        xS16Z.To__Array(bZ, 0)

        SIL3.MemoryCopy.MemoryCopy.Copy_Memory(ps16X, bX, 2)
        SIL3.MemoryCopy.MemoryCopy.Copy_Memory(ps16Y, bY, 2)
        SIL3.MemoryCopy.MemoryCopy.Copy_Memory(ps16Z, bZ, 2)

    End Sub

#End Region '#Region "MMA8451"

#Region "FWD LASER"

#End Region '#Region "FWD LASER"

#Region "STEPPER"

    ''' <summary>
    ''' Update from the stepper system with its new position
    ''' </summary>
    ''' <param name="u8MotorIndex"></param>
    ''' <param name="u8Step"></param>
    ''' <param name="u8Dir"></param>
    ''' <param name="s32Position"></param>
    Private Sub STEPDRIVE_WIN32__UpdatePostion(u8MotorIndex As Byte, u8Step As Byte, u8Dir As Byte, s32Position As Int32)

        Select Case u8MotorIndex
            Case 0
                Threadsafe__SetText(Me.m_txtBrakeL_Pos, s32Position.ToString)

                'compute the MLP value
                '0 = 2^12 is the ADC range

                Dim sMLP As Single = s32Position + 7500

                'convert to mm
                sMLP /= 1000.0
                'convert to percent
                sMLP /= 75.0
                'down to 75% of that again to add some head room
                sMLP *= 0.75
                'convert to ADC values
                sMLP *= (2 ^ 12)


                Me.m_iL_MLP = CInt(sMLP)
                vFCU_BRAKES_MLP_WIN32__ForceADC(0, CUShort(sMLP))

                '75mm
                If s32Position > 750000 Then
                    vFCU_BRAKES_SW_WIN32__Inject_SwitchState(0, 1, 1)
                    vFCU_BRAKES_SW__Left_SwitchExtend_ISR()
                ElseIf s32Position < -300 Then
                    'fake some cal limit
                    vFCU_BRAKES_SW_WIN32__Inject_SwitchState(0, 0, 1)
                    vFCU_BRAKES_SW__Left_SwitchRetract_ISR()
                Else
                    vFCU_BRAKES_SW_WIN32__Inject_SwitchState(0, 1, 0)
                    vFCU_BRAKES_SW_WIN32__Inject_SwitchState(0, 0, 0)
                End If

            Case 1
                Threadsafe__SetText(Me.m_txtBrakeR_Pos, s32Position.ToString)

                'make a simple little simulation model
                'if the brake position is < 0 hit the limit swiches
                '75mm
                If s32Position > 750000 Then
                    vFCU_BRAKES_SW_WIN32__Inject_SwitchState(1, 1, 1)
                    vFCU_BRAKES_SW__Right_SwitchExtend_ISR()
                ElseIf s32Position < -120 Then
                    'fake some cal limit
                    vFCU_BRAKES_SW_WIN32__Inject_SwitchState(1, 0, 1)
                    vFCU_BRAKES_SW__Right_SwitchRetract_ISR()
                Else
                    vFCU_BRAKES_SW_WIN32__Inject_SwitchState(1, 0, 0)
                    vFCU_BRAKES_SW_WIN32__Inject_SwitchState(1, 1, 0)
                End If


        End Select

    End Sub
#End Region '#Region "STEPPER

#Region "SC16IS"

    ''' <summary>
    ''' Called when a SC16IS wants to transmit
    ''' </summary>
    ''' <param name="u8DeviceIndex"></param>
    ''' <param name="pu8Data"></param>
    ''' <param name="u8Length"></param>
    Private Sub SC16IS_WIN32__TxData(u8DeviceIndex As Byte, pu8Data As IntPtr, u8Length As Byte)

        Dim pu8Array() As Byte
        ReDim pu8Array(u8Length - 1)

        SIL3.MemoryCopy.MemoryCopy.Copy_Memory(pu8Array, pu8Data, CInt(u8Length))

        Select Case u8DeviceIndex
            Case 0
                'OptoNCDT
            Case 1
                'OptoNCDT
            Case 2
                'OptoNCDT
            Case 3
                'OptoNCDT
            Case 4
                'OptoNCDT
            Case 5
                'OptoNCDT

            Case 6
                'Fwd Laser
            Case 7
                'ASI Controller Network
                'determine what ASI was configured last
                Dim iIndex As Integer = u8FCU_ASI_MUX_WIN32__Get()

                'copy bytes into that ASI
                For iCounter As Integer = 0 To u8Length - 1
                    Me.m_pASI(iIndex).Byte_In(pu8Array(iCounter))
                Next

        End Select
    End Sub

#End Region '#Region "SC16IS"

#Region "AMC7812 DAC"
    ''' <summary>
    ''' The DAC has updated us with its volts
    ''' </summary>
    ''' <param name="u8Channel"></param>
    ''' <param name="f32Value"></param>
    Private Sub AMC7182_DAC__SetVolts(u8Channel As Byte, f32Value As Single)
        'tell our ASI about it.
        Me.m_pASI(u8Channel).Voltage__Update(f32Value)
        Me.Threadsafe__SetText(Me.m_txtASI_Volts(u8Channel), f32Value.ToString("0.000"))
    End Sub

#End Region '#Region "AMC7812 DAC"

#Region "ASI"
    ''' <summary>
    ''' ASI wants to transmit
    ''' </summary>
    ''' <param name="u8Array"></param>
    ''' <param name="iLength"></param>
    Private Sub ASI_Tx_RS485(u8Array() As Byte, iLength As Integer)

        'Inject into SC16
        'channel 7 is the RS485
        vSC16IS_WIN32__InjectData(7, u8Array, iLength)

    End Sub
#End Region '#Region "ASI"

End Class


''' <summary>
''' Just a Fake CM30 laser
''' </summary>
Public Class CM30Laser

End Class


''' <summary>
''' Mock ASI controller interface
''' </summary>
Public Class ASIController

#Region "DLL"
    Private Const C_DLL_NAME As String = "..\..\..\PROJECT_CODE\DLLS\LDLL174__RLOOP__LCCM655\bin\Debug\LDLL174__RLOOP__LCCM655.dll"
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Function u16FCU_ASI_CRC__ComputeCRC(pu8Data() As Byte, u16DataLen As UInt16) As UInt16
    End Function

#End Region '#Region "DLL"

#Region "MEMBERS"

    ''' <summary>
    ''' The count of Rx Bytes
    ''' </summary>
    Private m_iRxCount As Integer

    ''' <summary>
    ''' Holding array for Rx bytes
    ''' </summary>
    Private m_bRxArray() As Byte

    ''' <summary>
    ''' Transmit return array
    ''' </summary>
    Private m_bTxArray() As Byte

    ''' <summary>
    ''' Our internal voltage which is the RPM
    ''' </summary>
    Private m_f32Volts As Single

    ''' <summary>
    ''' The fault register
    ''' </summary>
    Private m_u16Reg__Faults As SIL3.Numerical.U16

#End Region '#Region "MEMBERS"

#Region "NEW"

    ''' <summary>
    ''' New instance
    ''' </summary>
    Public Sub New()
        'init
        ReDim Me.m_bRxArray(8 - 1)
        ReDim Me.m_bTxArray(7 - 1)

        'set some values
        Me.m_u16Reg__Faults = New SIL3.Numerical.U16(0)
    End Sub

#End Region '#Region "NEW"

#Region "EVENTS"

    ''' <summary>
    ''' Called when we want to Tx a packet
    ''' </summary>
    ''' <param name="u8Array"></param>
    ''' <param name="iLength"></param>
    Public Event Tx_RS485(u8Array() As Byte, iLength As Integer)
#End Region '#Region "EVENTS"

#Region "RX"
    ''' <summary>
    ''' Rx some new byte of data for the ASI
    ''' </summary>
    ''' <param name="u8Value"></param>
    Public Sub Byte_In(u8Value As Byte)
        Me.m_bRxArray(Me.m_iRxCount) = u8Value
        Me.m_iRxCount += 1

        'handle the processing
        If Me.m_iRxCount = 8 Then

            'do the processing
            Select Case m_bRxArray(0)
                Case &H1
                    'slave addx 01

                    Select Case m_bRxArray(1)
                        Case &H3
                            'read holding registers

                            'reg addx h,l
                            Dim u16Reg As New SIL3.Numerical.U16(Me.m_bRxArray(2), Me.m_bRxArray(3))

                            'num regs, hl,
                            Dim u16Num As New SIL3.Numerical.U16(Me.m_bRxArray(4), Me.m_bRxArray(5))
                            'crc h,l
                            Dim u16CRC As New SIL3.Numerical.U16(Me.m_bRxArray(6), Me.m_bRxArray(7))

                            Select Case u16Reg.To__Int
                                Case &H102
                                    'faults

                                    'gen our return array
                                    'id
                                    Me.m_bTxArray(0) = Me.m_bRxArray(0)
                                    'read holding regs
                                    Me.m_bTxArray(1) = 3
                                    'num *2
                                    Me.m_bTxArray(2) = 1 * 2
                                    'reg value
                                    Me.m_u16Reg__Faults.To__Array(Me.m_bTxArray, 3)
                                    'crc
                                    Dim u16Temp As UInt16
                                    u16Temp = u16FCU_ASI_CRC__ComputeCRC(Me.m_bTxArray, 7 - 2)

                                    Dim pu16 As New SIL3.Numerical.U16(u16Temp)
                                    pu16.To__Array(Me.m_bTxArray, 5)

                                    'transmit it
                                    RaiseEvent Tx_RS485(Me.m_bTxArray, 7)
                            End Select

                    End Select

            End Select

            'done with it now
            Me.m_iRxCount = 0
        End If

    End Sub

#End Region '#Region "RX"

#Region "VOLTAGE / THROTTLE"
    ''' <summary>
    ''' Update our voltage.
    ''' </summary>
    ''' <param name="f32Voltage"></param>
    Public Sub Voltage__Update(f32Voltage As Single)
        Me.m_f32Volts = f32Voltage
    End Sub

#End Region '#Region "VOLTAGE / THROTTLE"

End Class