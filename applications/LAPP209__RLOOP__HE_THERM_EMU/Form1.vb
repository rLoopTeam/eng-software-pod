Imports System.ComponentModel


''' <summary>
''' Basic framework for rLoop Auxiliary Propultion Controler
''' Lachlan Grogan - @SafetyLok
''' </summary>
Public Class Form1

#Region "CONSTANTS"

    Private Const C_IP_PORT As Integer = 9608

    ''' <summary>
    ''' number of sensors on each side.
    ''' </summary>
    Private Const C_NUM_SENSORS_PER_SIDE As Integer = 8

    Private Const C_NUM_SOLENOIDS As Integer = 2

#End Region '#Region "CONSTANTS"

#Region "DLL HANDLING"

    ''' <summary>
    ''' The name of our DLL, could be a bit better done with relative paths
    ''' </summary>
    Private Const C_DLL_NAME As String = "..\..\..\PROJECT_CODE\DLLS\LDLL181__RLOOP__LCCM721\bin\Debug\LDLL181__RLOOP__LCCM721.dll"

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
    Public Delegate Sub SIL3_DEBUG_PRINTF__CallbackDelegate(ByVal pu8String As IntPtr)


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
    Public Delegate Sub SIL3_ETH_WIN32__TxCallbackDelegate(ByVal pu8Buffer As IntPtr, ByVal u16BufferLength As UInt16)


    'APU Things
    <System.Runtime.InteropServices.UnmanagedFunctionPointerAttribute(System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Public Delegate Sub HETHERM_WIN32__UpdateData__Delegate(u8SolL As Byte, u8SolR As Byte)

    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Public Shared Sub vHETHERM_WIN32__SetCallback_UpdateData(ByVal callback As MulticastDelegate)
    End Sub


#End Region '#Region "WIN32/DEBUG"

#Region "C CODE SPECIFICS"

    ''' <summary>
    ''' The Init function from the power node
    ''' </summary>
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vHETHERM__Init()
    End Sub

    ''' <summary>
    ''' the process function from the power node
    ''' </summary>
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vHETHERM__Process()
    End Sub


    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vHETHERM_TIMERS__10MS_ISR()
    End Sub
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vHETHERM_TIMERS__100MS_ISR()
    End Sub


#End Region '#Region "C CODE SPECIFICS"

#End Region '#Region "DLL HANDLING"

#Region "MEMBERS"

    ''' <summary>
    ''' Our output text box used for serial debugging
    ''' </summary>
    ''' <remarks></remarks>
    Private m_txtOutput As Windows.Forms.TextBox

    ''' <summary>
    ''' The array of sensors
    ''' </summary>
    Private m_Sensor() As ThermalSensor

    Private m_pSol() As Solenoid

    ''' <summary>
    ''' The debug delegate for screen printing.
    ''' </summary>
    ''' <remarks></remarks>
    Private m_pSIL3_DEBUG_PRINTF_WIN32__Delegate As SIL3_DEBUG_PRINTF__CallbackDelegate

    ''' <summary>
    ''' Callbacks for the ethernet interface
    ''' </summary>
    Private m_pSIL3_ETH_WIN32_TX__Delegate As SIL3_ETH_WIN32__TxCallbackDelegate

    Private m_pHETHERM_WIN32__UpdateData__Delegate As HETHERM_WIN32__UpdateData__Delegate

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

    Private m_pTimer10m As System.Timers.Timer
    Private m_pTimer100m As System.Timers.Timer


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
        Me.Text = "rLoop HE Thermal Emulator (Build: " & My.Application.Info.Version.ToString & ")"
        Me.BackColor = System.Drawing.Color.White
        Me.WindowState = FormWindowState.Maximized

        'create a panel inside our form which is easy to add stuff to
        Dim pP As New Panel
        With pP
            .BackColor = System.Drawing.Color.White
            .Dock = DockStyle.Fill
            .AutoScroll = True
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


        ReDim Me.m_Sensor(((C_NUM_SENSORS_PER_SIDE * 2) + 2) - 1)
        Dim iIndex As Integer = 0
        For iCounter As Integer = 0 To C_NUM_SENSORS_PER_SIDE - 1
            Me.m_Sensor(iIndex) = New ThermalSensor(iIndex)
            Me.m_Sensor(iIndex).Location = New Point(10, (pB1.Top + pB1.Height + 10) + (Me.m_Sensor(iIndex).Size.Height + 5) * iCounter)
            pP.Controls.Add(Me.m_Sensor(iIndex))
            iIndex += 1
        Next

        iIndex = C_NUM_SENSORS_PER_SIDE
        For iCounter As Integer = 0 To C_NUM_SENSORS_PER_SIDE - 1
            Me.m_Sensor(iIndex) = New ThermalSensor(iIndex)
            Me.m_Sensor(iIndex).Location = New Point(800, (pB1.Top + pB1.Height + 10) + (Me.m_Sensor(iIndex).Size.Height + 5) * iCounter)
            pP.Controls.Add(Me.m_Sensor(iIndex))
            iIndex += 1
        Next

        ReDim Me.m_pSol(C_NUM_SOLENOIDS - 1)


        iIndex = (C_NUM_SENSORS_PER_SIDE * 2) + 0
        Me.m_Sensor(iIndex) = New ThermalSensor(iIndex)
        Me.m_Sensor(iIndex).Location = New Point(Me.m_Sensor(3).Location.X + Me.m_Sensor(3).Size.Width + 5, Me.m_Sensor(3).Location.Y)
        pP.Controls.Add(Me.m_Sensor(iIndex))
        Me.m_pSol(0) = New Solenoid(0)
        Me.m_pSol(0).Location = New Point(Me.m_Sensor(iIndex).Location.X, Me.m_Sensor(iIndex).Location.Y + Me.m_Sensor(iIndex).Size.Height + 5)
        pP.Controls.Add(Me.m_pSol(0))


        iIndex += 1
        Me.m_Sensor(iIndex) = New ThermalSensor(iIndex)
        Me.m_Sensor(iIndex).Location = New Point(Me.m_Sensor(11).Location.X - 5 - Me.m_Sensor(iIndex).Width, Me.m_Sensor(11).Location.Y)
        pP.Controls.Add(Me.m_Sensor(iIndex))

        Me.m_pSol(1) = New Solenoid(1)
        Me.m_pSol(1).Location = New Point(Me.m_Sensor(iIndex).Location.X, Me.m_Sensor(iIndex).Location.Y + Me.m_Sensor(iIndex).Size.Height + 5)
        pP.Controls.Add(Me.m_pSol(1))



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
        If Not m_pMainThread Is Nothing Then
            Me.m_pMainThread.Abort()
        End If

        If Not m_pTimer10m Is Nothing Then
            Me.m_pTimer10m.Stop()
            Me.m_pTimer100m.Stop()
        End If

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


        Me.m_pSafeUDP = New SIL3.SafeUDP.StdUDPLayer("127.0.0.1", C_IP_PORT, "HETHERM_ETH_EMU", True, True)
        AddHandler Me.m_pSafeUDP.UserEvent__UDPSafe__RxPacket, AddressOf Me.InernalEvent__UDPSafe__RxPacket
        AddHandler Me.m_pSafeUDP.UserEvent__NewPacket, AddressOf Me.InternalEvent__NewPacket

        'Seup the debugging support if needed
        Me.m_pSIL3_DEBUG_PRINTF_WIN32__Delegate = AddressOf Me.SIL3_DEBUG_PRINTF_WIN32_Callback
        vSIL3_DEBUG_PRINTF_WIN32__Set_Callback(Me.m_pSIL3_DEBUG_PRINTF_WIN32__Delegate)

        'setup other callbacks

        Me.m_pSIL3_ETH_WIN32_TX__Delegate = AddressOf Me.ETH_WIN32__TxCallback_Sub
        vSIL3_ETH_WIN32__Set_Ethernet_TxCallback(Me.m_pSIL3_ETH_WIN32_TX__Delegate)

        Me.m_pHETHERM_WIN32__UpdateData__Delegate = AddressOf Me.HETHERM_WIN32__UpdateData__Callback
        vHETHERM_WIN32__SetCallback_UpdateData(Me.m_pHETHERM_WIN32__UpdateData__Delegate)




        'stimers
        Timers__Setup()

    End Sub
#End Region '#Region "SYSTEM INIT"

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
        'vLCCM655R0_TS_003()

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

            'do the threading
            Me.m_pMainThread = New Threading.Thread(AddressOf Me.Thread__Main)
            Me.m_pMainThread.Name = "HETHERM THREAD"
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

        'call Init
        vHETHERM__Init()

        'needs to be done due to WIN32_ETH_Init
        vSIL3_ETH_WIN32__Set_Ethernet_TxCallback(Me.m_pSIL3_ETH_WIN32_TX__Delegate)


        'stay here until thread abort
        While True

            'add here any things that need updating like pod sensor data

            'call process
            Try
                vHETHERM__Process()

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

        Me.m_pTimer10m = New System.Timers.Timer
        Me.m_pTimer10m.Interval = 10
        AddHandler Me.m_pTimer10m.Elapsed, AddressOf Me.Timers__T10_Tick
        Me.m_pTimer10m.Start()

        Me.m_pTimer100m = New System.Timers.Timer
        Me.m_pTimer100m.Interval = 100
        AddHandler Me.m_pTimer100m.Elapsed, AddressOf Me.Timers__T100_Tick
        Me.m_pTimer100m.Start()


    End Sub


    ''' <summary>
    ''' 10ms timer
    ''' </summary>
    ''' <param name="s"></param>
    ''' <param name="e"></param>
    Private Sub Timers__T10_Tick(s As Object, e As System.Timers.ElapsedEventArgs)
        If Me.m_bThreadRun = True Then
            vHETHERM_TIMERS__10MS_ISR()
        End If
    End Sub

    ''' <summary>
    ''' 100ms timer
    ''' </summary>
    ''' <param name="s"></param>
    ''' <param name="e"></param>
    Private Sub Timers__T100_Tick(s As Object, e As System.Timers.ElapsedEventArgs)
        If Me.m_bThreadRun = True Then
            vHETHERM_TIMERS__100MS_ISR()
        End If
    End Sub



#End Region '#Region "TIMERS"

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

        Dim iEthPort As Integer = C_IP_PORT
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

#Region "HE THERMAL"

    Private Sub HETHERM_WIN32__UpdateData__Callback(u8SolL As Byte, u8SolR As Byte)



    End Sub

#End Region '#Region "APU"

    Public Class ThermalSensor
        Inherits Windows.Forms.Panel

#Region "MEMBERS"
        ''' <summary>
        ''' The track bar
        ''' </summary>
        Private m_pTrk As TrackBar

        ''' <summary>
        ''' Shows our temperature
        ''' </summary>
        Private m_lTemp As Label

        ''' <summary>
        ''' Our device ID
        ''' </summary>
        Private m_lID As Label

        ''' <summary>
        ''' The bus index
        ''' </summary>
        Private m_iDeviceIndex As Integer

#End Region

        Public Sub New(iDeviceIndex As Integer)
            MyBase.New
            m_iDeviceIndex = iDeviceIndex

            MyBase.Size = New Size(200, 70)
            MyBase.BorderStyle = BorderStyle.FixedSingle

            Me.m_lID = New Label
            With Me.m_lID
                .Location = New Point(10, 5)
                .Font = New Font("Arial", 6)
                .Text = "Device ID: 0xAABBCCDD"
                .BringToFront()
            End With
            MyBase.Controls.Add(Me.m_lID)

            Me.m_pTrk = New TrackBar
            With Me.m_pTrk
                .Location = New Point(5, Me.m_lID.Location.Y + Me.m_lID.Size.Height)
                .Size = New Size(100, 20)
                .Minimum = -20
                .Maximum = 120
                .Value = 27
                .LargeChange = 10
                .SmallChange = 1
                .TickFrequency = 10
            End With
            MyBase.Controls.Add(Me.m_pTrk)
            AddHandler Me.m_pTrk.ValueChanged, AddressOf Me.pTrack__ValueChanged

            Me.m_lTemp = New Label
            With Me.m_lTemp
                .Location = New Point(Me.m_pTrk.Location.X + Me.m_pTrk.Size.Width + 10, Me.m_pTrk.Location.Y)
                .Font = New Font("Arial", 14, FontStyle.Bold)
                .Text = "27.0C"
            End With
            MyBase.Controls.Add(Me.m_lTemp)


        End Sub

        Private Sub pTrack__ValueChanged(sender As Object, e As EventArgs)
            Me.m_lTemp.Text = CSng(Me.m_pTrk.Value).ToString("0.0") & " C"
        End Sub


    End Class


    Public Class Solenoid
        Inherits Windows.Forms.Panel

#Region "MEMBERS"

        ''' <summary>
        ''' Shows our temperature
        ''' </summary>
        Private m_lTemp As Label

        ''' <summary>
        ''' Solenoid state
        ''' </summary>
        Private m_picState As PictureBox

        ''' <summary>
        ''' The bus index
        ''' </summary>
        Private m_iDeviceIndex As Integer

        ''' <summary>
        ''' Our device ID
        ''' </summary>
        Private m_lID As Label

#End Region

        Public Sub New(iDeviceIndex As Integer)
            MyBase.New

            m_iDeviceIndex = iDeviceIndex
            MyBase.Size = New Size(200, 70)
            MyBase.BorderStyle = BorderStyle.FixedSingle

            Me.m_lID = New Label
            With Me.m_lID
                .Location = New Point(10, 5)
                .Font = New Font("Arial", 6)
                .Text = "Device ID: 0xAABBCCDD"
                .BringToFront()
            End With
            MyBase.Controls.Add(Me.m_lID)

            Me.m_picState = New PictureBox
            With Me.m_picState
                .Location = New Point(10, Me.m_lID.Location.Y + Me.m_lID.Size.Height + 1)
                .Size = New Size(25, 25)
                .BorderStyle = BorderStyle.FixedSingle
                .BackColor = Color.Red
            End With
            MyBase.Controls.Add(Me.m_picState)


            Me.m_lTemp = New Label
            With Me.m_lTemp
                .Location = New Point(Me.m_picState.Location.X + Me.m_picState.Size.Width + 10, Me.m_picState.Location.Y)
                .Font = New Font("Arial", 14, FontStyle.Bold)
                .Text = "Off"
            End With
            MyBase.Controls.Add(Me.m_lTemp)


        End Sub


    End Class

End Class

