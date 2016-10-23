Imports System.ComponentModel
''' <summary>
''' Basic framework for rLoop Pi-Comms Emulation
''' Lachlan Grogan - SafetyLok
''' </summary>
Public Class Form1

#Region "DLL HANDLING"



    ''' <summary>
    ''' The name of our DLL, could be a bit better done with relative paths
    ''' </summary>
    Private Const C_DLL_NAME As String = "..\..\..\PROJECT_CODE\DLLS\LDLL175__RLOOP__LCCM656\bin\Debug\LDLL175__RLOOP__LCCM656.dll"

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
#End Region '#Region "WIN32/DEBUG"

#Region "C CODE SPECIFICS"

    ''' <summary>
    ''' Test function
    ''' </summary>
    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vPICOMMS_WIN32__Test1()
    End Sub

#End Region '#Region "C CODE SPECIFICS"

#Region "TX FRAME HELPERS"

    <System.Runtime.InteropServices.UnmanagedFunctionPointerAttribute(System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Public Delegate Sub PICOMMS_WIN32_TxFrame__CallbackDelegate(ByVal pu8Array As IntPtr, u16Length As UInt16)

    <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
    Private Shared Sub vPICOMMS_WIN32__TxFrame_Set_Callback(ByVal callback As MulticastDelegate)
    End Sub
#End Region '#Region "TX FRAME HELPERS"

#End Region '#Region "DLL HANDLING"

#Region "MEMBERS"

    Private m_pTxFrame_Delegate As PICOMMS_WIN32_TxFrame__CallbackDelegate

    ''' <summary>
    ''' Our output text box used for serial debugging
    ''' </summary>
    ''' <remarks></remarks>
    Private m_txtOutput As Windows.Forms.TextBox

    ''' <summary>
    ''' Our node temperature value
    ''' </summary>
    Private m_txtNodeTemp As TextBox

    ''' <summary>
    ''' The debug delegate
    ''' </summary>
    ''' <remarks></remarks>
    Private m_pDebug_Delegate As DEBUG_PRINTF__CallbackDelegate

    ''' <summary>
    ''' The thread to run our DLL in
    ''' </summary>
    ''' <remarks></remarks>
    Private m_pMainThread As Threading.Thread

    ''' <summary>
    ''' Global flag to indicate the thread is running
    ''' </summary>
    Private m_bThreadRun As Boolean


#End Region '#Region "MEMBERS"

#Region "FORM LAYOUT"

    ''' <summary>
    ''' Create the form
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles Me.Load

        'setup our form text and size
        Me.Text = "rLoop Pi Comms Emulator (Build: " & My.Application.Info.Version.ToString & ")"
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
            .Text = "Test"
        End With
        pP.Controls.Add(pB1)
        AddHandler pB1.Click, AddressOf Me.btnTest1__Click


        ''create some input item.
        'Dim l1 As New Label
        'With l1
        '    .Location = New Point(10, pB1.Top + pB1.Height + 20)
        '    .Text = "Some Input."
        'End With
        'pP.Controls.Add(l1)
        'Me.m_txtNodeTemp = New TextBox
        'With Me.m_txtNodeTemp
        '    .Location = New Point(10, l1.Top + l1.Height + 0)
        '    .Size = New Size(100, 24)
        '    .Text = "27.0"
        'End With
        'pP.Controls.Add(Me.m_txtNodeTemp)
        'AddHandler Me.m_txtNodeTemp.KeyDown, AddressOf Me.txtNodeTemp__KeyDown


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
    End Sub


#End Region '#Region "FORM LAYOUT"

#Region "SYSTEM INIT"
    ''' <summary>
    ''' Setup anyting else on the system
    ''' </summary>
    Private Sub Setup_System()

        'Seup the debugging support if needed
        Me.m_pDebug_Delegate = AddressOf Me.DEBUG_PRINTF_WIN32_Callback
        vDEBUG_PRINTF_WIN32__Set_Callback(Me.m_pDebug_Delegate)

        'setup other callbacks
        Me.m_pTxFrame_Delegate = AddressOf Me.PICOMMS_WIN32_TxFrame_Callback
        vPICOMMS_WIN32__TxFrame_Set_Callback(Me.m_pTxFrame_Delegate)


        'do the threading
        Me.m_pMainThread = New Threading.Thread(AddressOf Me.Thread__Main)
        Me.m_pMainThread.Name = "PICOMMS THREAD"

    End Sub
#End Region '#Region "SYSTEM INIT"

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


            End If
        End If
    End Sub
#End Region '#Region "KEY PRESS HANDLERS"

#Region "BUTTON HANDLERS"

    ''' <summary>
    ''' Test case 1
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    Private Sub btnTest1__Click(sender As Object, e As EventArgs)

        'call the code in the .dll
        vPICOMMS_WIN32__Test1()
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

#Region "THREADING"
    ''' <summary>
    ''' This is the same as Main() in C
    ''' </summary>
    Private Sub Thread__Main()

        'call Init

        'stay here until thread abort
        While True

            'add here any things that need updating like pod sensor data

            'call process

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

#Region "TX COMMS"
    ''' <summary>
    ''' Called when the PiComms layer wants to tx an array
    ''' </summary>
    ''' <param name="pu8Array"></param>
    ''' <remarks></remarks>
    Private Sub PICOMMS_WIN32_TxFrame_Callback(ByVal pu8Array As IntPtr, u16Length As UInt16)

        Dim bArray() As Byte

        'update the array
        ReDim bArray(u16Length - 1)

        'copy 128 bytes of memory, does not matter if we copy more than is needed
        CopyMemory(bArray, pu8Array, u16Length)

        'conver the array and spit it out
        Dim iSubCount As Integer = 0
        For iCounter As Integer = 0 To u16Length - 1

            Me.Threadsafe__AppendText(Me.m_txtOutput, "0x" & bArray(iCounter).ToString("x" & 2).ToUpper & " ")

        Next
    End Sub
#End Region

End Class
