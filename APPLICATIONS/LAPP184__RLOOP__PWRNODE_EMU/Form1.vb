Imports System.ComponentModel
''' <summary>
''' Basic framework for rLoop Power Node Emulation
''' Lachlan Grogan - SafetyLok
''' </summary>
Public Class Form1

#Region "CONSTANTS"

    ''' <summary>
    ''' The leak rate of the pressure vessel per second
    ''' </summary>
    Private Const C_PV_LEAK_RATE__BAR_SEC As Single = 0.00001

    Private Const C_ETH_PORT As Integer = 9110

#End Region '#Region "CONSTANTS"

#Region "DLL HANDLING"

    ''' <summary>
    ''' The name of our DLL, could be a bit better done with relative paths
    ''' </summary>
    Private Const C_DLL_NAME As String = "..\..\..\PROJECT_CODE\DLLS\LDLL173__RLOOP__LCCM653\bin\Debug\LDLL173__RLOOP__LCCM653.dll"

    ''' <summary>
    ''' Battery model
    ''' </summary>
    Private Const C_BATTERY_DLL_NAME As String = "..\..\..\COMMON_CODE\DLLS\LDLL186__MULTICORE__LCCM723\bin\Debug\LDLL186__MULTICORE__LCCM723.dll"


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
    Private Shared Sub vSIL3_DEBUG_PRINTF_WIN32__Set_Callback(ByVal callback As MulticastDelegate)
    End Sub


    'Ethernet
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Public Shared Sub vSIL3_ETH_WIN32__Set_Ethernet_TxCallback(ByVal callback As MulticastDelegate)
    End Sub
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Public Shared Sub vSIL3_ETH_WIN32__Ethernet_Input(pu8Buffer() As Byte, u16BufferLength As UInt16)
    End Sub
    <System.Runtime.InteropServices.UnmanagedFunctionPointerAttribute(System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Public Delegate Sub ETH_WIN32__TxCallbackDelegate(ByVal pu8Buffer As IntPtr, ByVal u16BufferLength As UInt16)



#End Region '#Region "WIN32/DEBUG"

#Region "C CODE SPECIFICS"

    ''' <summary>
    ''' The Init function from the power node
    ''' </summary>
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vPWRNODE__Init()
    End Sub

    ''' <summary>
    ''' the process function from the power node
    ''' </summary>
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vPWRNODE__Process()
    End Sub

    'set the temp on the node
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vPWRNODE_WIN32__Set_NodeTemperature(f32Temperature As Single)
    End Sub
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vPWRNODE_WIN32__Set_NodePressure(f32Temperature As Single)
    End Sub

    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vPWRNODE__RTI_100MS_ISR()
    End Sub
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vPWRNODE__RTI_10MS_ISR()
    End Sub
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vPWRNODE_WIN32__Set_NodePersonality(u8Value As Byte)
    End Sub
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Function u8PWRNODE_WIN32__Get_RepressSolState() As Byte
    End Function
#End Region '#Region "C CODE SPECIFICS"

#Region "BATTERY SPECIFICS"

    <System.Runtime.InteropServices.DllImport(C_BATTERY_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vLIPOMODEL__Init()
    End Sub
    <System.Runtime.InteropServices.DllImport(C_BATTERY_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vLIPOMODEL__Process()
    End Sub
    <System.Runtime.InteropServices.DllImport(C_BATTERY_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vLIPOMODEL__1S_ISR()
    End Sub

    <System.Runtime.InteropServices.DllImport(C_BATTERY_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Function f32LIPOMODEL_WIN32__Get_PackVoltage(u16PackIndex As UInt16) As Single
    End Function


#End Region '#Region "BATTERY SPECIFICS"

#End Region '#Region "DLL HANDLING"

#Region "MEMBERS"
    ''' <summary>
    ''' Our output text box used for serial debugging
    ''' </summary>
    ''' <remarks></remarks>
    Private m_txtOutput As Windows.Forms.TextBox

    ''' <summary>
    ''' Allows us to choose which index we want
    ''' </summary>
    Private m_cboNodeIndex As ComboBox
    Private m_bNodeIndex As Byte

    ''' <summary>
    ''' Our node temperature value
    ''' </summary>
    Private m_txtNodeTemp As TextBox

    ''' <summary>
    ''' Node pressure box
    ''' </summary>
    Private m_txtNodePress As TextBox

    ''' <summary>
    ''' Repress Solenoid
    ''' </summary>
    Private m_chkPressSol As CheckBox

    Private m_txtBatteryV As TextBox

    ''' <summary>
    ''' The debug delegate
    ''' </summary>
    ''' <remarks></remarks>
    Private m_pDebug_Delegate As DEBUG_PRINTF__CallbackDelegate

    ''' <summary>
    ''' Ethernet transmit
    ''' </summary>
    Private m_pETH_TX__Delegate As ETH_WIN32__TxCallbackDelegate


    ''' <summary>
    ''' The thread to run our DLL in
    ''' </summary>
    ''' <remarks></remarks>
    Private m_pMainThread As Threading.Thread

    ''' <summary>
    ''' Global flag to indicate the thread is running
    ''' </summary>
    Private m_bThreadRun As Boolean

    Private m_pSafeUDP As LAPP184__RLOOP__LIB.SIL3.SafeUDP.StdUDPLayer


    Private m_pTimer10m As System.Timers.Timer
    Private m_pTimer100m As System.Timers.Timer
    Private m_pTimer1s As System.Timers.Timer

#End Region '#Region "MEMBERS"

#Region "FORM LAYOUT"

    ''' <summary>
    ''' Create the form
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles Me.Load

        'setup our form text and size
        Me.Text = "rLoop Power Node Emulator (Build: " & My.Application.Info.Version.ToString & ")"
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

        Me.m_cboNodeIndex = New ComboBox
        With Me.m_cboNodeIndex
            .Location = New Point(pB1.Location.X + pB1.Size.Width + 5, pB1.Location.Y)
            .Size = New Size(100, 24)

        End With
        Me.m_cboNodeIndex.Items.Add("Node A")
        Me.m_cboNodeIndex.Items.Add("Node B")
        Me.m_cboNodeIndex.SelectedIndex = 0
        pP.Controls.Add(Me.m_cboNodeIndex)


        'create some node temperature items
        Dim l1 As New Label
        With l1
            .Location = New Point(10, pB1.Top + pB1.Height + 20)
            .Text = "TSYS01 Temp."
        End With
        pP.Controls.Add(l1)
        Me.m_txtNodeTemp = New TextBox
        With Me.m_txtNodeTemp
            .Location = New Point(10, l1.Top + l1.Height + 0)
            .Size = New Size(100, 24)
            .Text = "27.0"
        End With
        pP.Controls.Add(Me.m_txtNodeTemp)
        AddHandler Me.m_txtNodeTemp.KeyDown, AddressOf Me.txtNodeTemp__KeyDown


        Dim l2 As New Label
        With l2
            .Location = New Point(Me.m_txtNodeTemp.Location.X + Me.m_txtNodeTemp.Size.Width + 10, l1.Top)
            .Text = "Pressure (Bar)"
        End With
        pP.Controls.Add(l2)
        Me.m_txtNodePress = New TextBox
        With Me.m_txtNodePress
            .Location = New Point(l2.Location.X, l2.Top + l2.Height + 0)
            .Size = New Size(100, 24)
            .Text = "1.00000"
        End With
        pP.Controls.Add(Me.m_txtNodePress)
        AddHandler Me.m_txtNodePress.KeyDown, AddressOf Me.txtNodePress__KeyDown

        'add the PV repress solenoid
        Me.m_chkPressSol = New CheckBox
        With Me.m_chkPressSol
            .Location = New Point(Me.m_txtNodePress.Location.X + Me.m_txtNodePress.Size.Width + 10, Me.m_txtNodePress.Location.Y)
            .Text = "Solenoid"
            .Enabled = False
        End With
        pP.Controls.Add(Me.m_chkPressSol)

        Dim l3 As New Label
        With l3
            .Location = New Point(Me.m_txtNodeTemp.Location.X, Me.m_txtNodeTemp.Top + Me.m_txtNodeTemp.Height + 10)
            .Text = "Battery"
        End With
        pP.Controls.Add(l3)
        Me.m_txtBatteryV = New TextBox
        With Me.m_txtBatteryV
            .Location = New Point(l3.Location.X, l3.Top + l3.Height + 0)
            .Size = New Size(100, 24)
            .Text = ""
        End With
        pP.Controls.Add(Me.m_txtBatteryV)





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


        Me.m_pSafeUDP = New LAPP184__RLOOP__LIB.SIL3.SafeUDP.StdUDPLayer("127.0.0.1", C_ETH_PORT, "PWR_A_ETH_EMU", True, True)
        AddHandler Me.m_pSafeUDP.UserEvent__UDPSafe__RxPacket, AddressOf Me.InernalEvent__UDPSafe__RxPacket
        AddHandler Me.m_pSafeUDP.UserEvent__NewPacket, AddressOf Me.InternalEvent__NewPacket


        'Seup the debugging support if needed
        Me.m_pDebug_Delegate = AddressOf Me.SIL3_DEBUG_PRINTF_WIN32_Callback
        vSIL3_DEBUG_PRINTF_WIN32__Set_Callback(Me.m_pDebug_Delegate)

        'setup other callbacks
        Me.m_pETH_TX__Delegate = AddressOf Me.ETH_WIN32__TxCallback_Sub
        vSIL3_ETH_WIN32__Set_Ethernet_TxCallback(Me.m_pETH_TX__Delegate)


        'config the timers
        Timers__Setup()

    End Sub
#End Region '#Region "SYSTEM INIT"

#Region "TIMERS"
    ''' <summary>
    ''' Start the timers.
    ''' </summary>
    Private Sub Timers__Setup()

        Me.m_pTimer10m = New System.Timers.Timer
        Me.m_pTimer10m.Interval = 10
        AddHandler Me.m_pTimer10m.Elapsed, AddressOf Me.Timers__T10_Tick
        Me.m_pTimer10m.Start()

        Me.m_pTimer100m = New System.Timers.Timer
        Me.m_pTimer100m.Interval = 100
        AddHandler Me.m_pTimer100m.Elapsed, AddressOf Me.Timers__T100_Tick
        Me.m_pTimer100m.Start()

        Me.m_pTimer1s = New System.Timers.Timer
        Me.m_pTimer1s.Interval = 1000
        AddHandler Me.m_pTimer1s.Elapsed, AddressOf Me.Timers__T1S_Tick
        Me.m_pTimer1s.Start()

    End Sub

    Private Sub Timers__T1S_Tick(s As Object, e As System.Timers.ElapsedEventArgs)
        If Me.m_bThreadRun = True Then

            'run the battery model
            vLIPOMODEL__1S_ISR()

            'run PV leak rate
            Dim sValue As Single = Single.Parse(Me.m_txtNodePress.Text)
            'leak
            sValue -= C_PV_LEAK_RATE__BAR_SEC

            'update
            vPWRNODE_WIN32__Set_NodePressure(sValue)
            Threadsafe__SetText(Me.m_txtNodePress, sValue.ToString("0.00000"))

            'see if the sol is on.
            If u8PWRNODE_WIN32__Get_RepressSolState() = 1 Then
                Me.m_chkPressSol.Checked = True
            Else
                Me.m_chkPressSol.Checked = False
            End If

            'battery
            Threadsafe__SetText(Me.m_txtBatteryV, f32LIPOMODEL_WIN32__Get_PackVoltage(0).ToString("0.000"))


        End If
    End Sub

    ''' <summary>
    ''' 10ms timer
    ''' </summary>
    ''' <param name="s"></param>
    ''' <param name="e"></param>
    Private Sub Timers__T10_Tick(s As Object, e As System.Timers.ElapsedEventArgs)
        If Me.m_bThreadRun = True Then
            vPWRNODE__RTI_10MS_ISR()
        End If
    End Sub

    ''' <summary>
    ''' 100ms timer
    ''' </summary>
    ''' <param name="s"></param>
    ''' <param name="e"></param>
    Private Sub Timers__T100_Tick(s As Object, e As System.Timers.ElapsedEventArgs)
        If Me.m_bThreadRun = True Then
            vPWRNODE__RTI_100MS_ISR()
        End If
    End Sub




#End Region '#Region "TIMERS"

#Region "KEY PRESS HANDLERS"
    ''' <summary>
    ''' Handles enter on the node temperature box
    ''' </summary>
    ''' <param name="s"></param>
    ''' <param name="e"></param>
    Private Sub txtNodeTemp__KeyDown(s As Object, e As KeyEventArgs)
        'handle enter key
        If e.KeyCode = Keys.Enter Then
            'check safety
            If Me.m_bThreadRun = False Then
                MsgBox("Warn: You must have thread running.")
            Else
                'convert string to float32 (single on WIN32)
                'todo, error checking
                Dim sValue As Single = Single.Parse(Me.m_txtNodeTemp.Text)
                vPWRNODE_WIN32__Set_NodeTemperature(sValue)
            End If
        End If
    End Sub

    Private Sub txtNodePress__KeyDown(s As Object, e As KeyEventArgs)
        'handle enter key
        If e.KeyCode = Keys.Enter Then
            'check safety
            If Me.m_bThreadRun = False Then
                MsgBox("Warn: You must have thread running.")
            Else
                'convert string to float32 (single on WIN32)
                'todo, error checking
                Dim sValue As Single = Single.Parse(Me.m_txtNodePress.Text)
                vPWRNODE_WIN32__Set_NodePressure(sValue)
            End If
        End If

    End Sub
#End Region

#Region "BUTTON HANDLERS"
    ''' <summary>
    ''' Called to start/stop
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    Private Sub btnStart__Click(sender As Object, e As EventArgs)

        'get the object
        Dim pB As Button = CType(sender, Button)

        If pB.Text = "Start" Then

            Me.m_bNodeIndex = Me.m_cboNodeIndex.SelectedIndex

            'set the flag
            Me.m_bThreadRun = True

            'set the new text
            pB.Text = "Stop"

            'start the thread
            Me.m_pMainThread = New Threading.Thread(AddressOf Me.Thread__Main)
            Me.m_pMainThread.Name = "POWERNODE THREAD"
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

#Region "THREADING"
    ''' <summary>
    ''' This is the same as Main() in C
    ''' </summary>
    Private Sub Thread__Main()

        'init the battery model
        vLIPOMODEL__Init()

        'call Init
        vPWRNODE__Init()

        'set our win32 personality
        vPWRNODE_WIN32__Set_NodePersonality(Me.m_bNodeIndex)

        'configure some default values
        Dim sValue As Single = Single.Parse(Me.m_txtNodeTemp.Text)
        vPWRNODE_WIN32__Set_NodeTemperature(sValue)
        sValue = Single.Parse(Me.m_txtNodePress.Text)
        vPWRNODE_WIN32__Set_NodePressure(sValue)

        'needs to be done due to WIN32_ETH_Init
        vSIL3_ETH_WIN32__Set_Ethernet_TxCallback(Me.m_pETH_TX__Delegate)


        'stay here until thread abort
        While True

            'process the battery model
            vLIPOMODEL__Process()

            'add here any things that need updating like pod sensor data

            'call process
            vPWRNODE__Process()

            'just wait a little bit
            Threading.Thread.Sleep(1)
        End While
    End Sub

#End Region '#Region "THREADING"

#Region "TEXT DEBUG"

    ''' <summary>
    ''' Called when the debug layer wants to print a string
    ''' </summary>
    ''' <param name="pu8String"></param>
    ''' <remarks></remarks>
    Private Sub SIL3_DEBUG_PRINTF_WIN32_Callback(ByVal pu8String As IntPtr)

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
            vSIL3_ETH_WIN32__Ethernet_Input(u8Array, iLength)
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
    Public Sub InernalEvent__UDPSafe__RxPacket(ByVal ePacketType As LAPP184__RLOOP__LIB.SIL3.SafeUDP.PacketTypes.SAFE_UDP__PACKET_T, ByVal u16PayloadLength As LAPP184__RLOOP__LIB.SIL3.Numerical.U16, ByRef u8Payload() As Byte, ByVal u16CRC As LAPP184__RLOOP__LIB.SIL3.Numerical.U16, ByVal bCRCOK As Boolean, ByVal u32Seq As UInt32)
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

            vSIL3_ETH_WIN32__Ethernet_Input(u8Buff, u16PayloadLength.To__Uint16 + 14)

        End If

    End Sub


    ''' <summary>
    ''' Called when teh DLL wants to trasmit eth data.
    ''' </summary>
    ''' <param name="u8Buffer"></param>
    ''' <param name="u16BufferLength"></param>
    ''' <remarks></remarks>
    Private Sub ETH_WIN32__TxCallback_Sub(ByVal u8Buffer As IntPtr, ByVal u16BufferLength As UInt16)

        Dim iEthPort As Integer = C_ETH_PORT
        Dim bArray(1500 - 1) As Byte
        LAPP184__RLOOP__LIB.SIL3.MemoryCopy.MemoryCopy.Copy_Memory(bArray, u8Buffer, CInt(u16BufferLength))


        'pass the packet off to our 802.3 layers
        Dim p802 As New LAPP184__RLOOP__LIB.SIL3.IEEE802_3.EthernetFrame(bArray, CInt(u16BufferLength), False)

        If p802.m_eEtherType = LAPP184__RLOOP__LIB.SIL3.IEEE802_3.EthernetFrame.eEtherType.Internet_Protocol_version_4 Then

            Dim p802_IPV4 As New LAPP184__RLOOP__LIB.SIL3.IEEE802_3.IPLayer.IPV4(p802.m_bPayload, p802.m_iPayloadLength)
            If p802_IPV4.m_pU8Protocol.To__Uint8 = &H11 Then

                Dim p802_UDP As New LAPP184__RLOOP__LIB.SIL3.IEEE802_3.UDP(p802_IPV4.m_bPayload, p802_IPV4.m_iPayloadLength)
                'If p802_UDP.m_pu16DestPort.To__Int = iEthPort Then

                'if we are here, we assume we are on loopback
                Dim pStdUDP As New LAPP184__RLOOP__LIB.SIL3.SafeUDP.StdUDPLayer("127.0.0.1", p802_UDP.m_pu16DestPort.To__Int) 'iEthPort)
                AddHandler pStdUDP.UserEvent__UDPSafe__RxPacket, AddressOf Me.UserEvent__UDPSafe__RxPacket

                'retransmit
                pStdUDP.UserEvent__NewUDP(p802_UDP, True)

                'End If

            End If

        End If


    End Sub

    Private Sub UserEvent__UDPSafe__RxPacket(ByVal ePacketType As LAPP184__RLOOP__LIB.SIL3.SafeUDP.PacketTypes.SAFE_UDP__PACKET_T, ByVal u16PayloadLength As LAPP184__RLOOP__LIB.SIL3.Numerical.U16, ByRef u8Payload() As Byte, ByVal u16CRC As LAPP184__RLOOP__LIB.SIL3.Numerical.U16, ByVal bCRC_OK As Boolean, ByVal u32Sequence As UInt32)


    End Sub


#End Region '#Region "ETH RX"

End Class
