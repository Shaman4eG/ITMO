Dim oSvc
Set oSvc = GetObject("WinMgmts:")
Dim objKeyb
Dim objProc
Dim objSound

Set xmlDocument = CreateObject("Microsoft.XMLDOM")  
Set objIntro = xmlDocument.createProcessingInstruction("xml","version='1.0'")  
xmlDocument.insertBefore objIntro,xmlDocument.childNodes(0)  
Set objRoot = xmlDocument.createElement("ComputerInfo")  
xmlDocument.appendChild objRoot  
	Set objKeyboard = xmlDocument.createElement("Keyboard") 
	objRoot.appendChild objKeyboard
		Set description = xmlDocument.createElement("Description")  
		objKeyboard.appendChild description  
		Set deviceID = xmlDocument.createElement("DeviceID")  
		objKeyboard.appendChild deviceID
		Set systemName = xmlDocument.createElement("SystemName")  
		objKeyboard.appendChild systemName
	Set objProcessor = xmlDocument.createElement("Processor") 
	objRoot.appendChild objProcessor
		Set caption = xmlDocument.createElement("Caption")  
		objProcessor.appendChild caption  
		Set name = xmlDocument.createElement("Name")  
		objProcessor.appendChild name
		Set manufacturer = xmlDocument.createElement("Manufacturer")  
		objProcessor.appendChild manufacturer
	Set objSound = xmlDocument.createElement("Sound") 
	objRoot.appendChild objSound
		Set caption2 = xmlDocument.createElement("Caption")  
		objSound.appendChild caption2
		Set manufacturer2 = xmlDocument.createElement("Manufacturer")  
		objSound.appendChild manufacturer2
		Set deviceID2 = xmlDocument.createElement("DeviceID")  
		objSound.appendChild deviceID2

For Each objKeyb In oSvc.ExecQuery("SELECT * FROM Win32_Keyboard")
	description.Text = objKeyb.Description 'описание устройства
	deviceID.Text = objKeyb.DeviceID 'адрес или другая уникальная информация идентификации
	systemName.Text = objKeyb.SystemName 'имя компьютера
Next

For Each objProc In oSvc.ExecQuery("SELECT * FROM Win32_Processor")
	caption.Text = objProc.Caption 'название процессора
	name.Text = objProc.Name 'наименование процессора
	manufacturer.Text = objProc.Manufacturer 'производитель
Next

For Each objSnd In oSvc.ExecQuery("SELECT * FROM Win32_SoundDevice")
	caption2.Text = objSnd.Caption 'наименование устройства
	manufacturer2.Text = objSnd.Manufacturer 'производитель
	deviceID2.Text = objSnd.DeviceID 'идентификатор устройства
Next

xmlDocument.Save "D:\Program Files\ITMO\Informatics\lab5\xmlDocument.xml"  
		



' On Error Resume Next
' Set objService = GetObject("winmgmts:{impersonationLevel=impersonate}!\\.\root\CIMV2")
' If Err.Number <> 0 Then
' 	WScript.Echo Err.Number & ": " & Err.Description
' 	WScript.Quit
' End If
' For Each objPnP In objService.ExecQuery("SELECT * FROM Win32_PnPEntity")
' 	WScript.Echo objPnP.Name 'наименование устройства
' 	WScript.Echo objPnP.Description 'описание устройства
' 	WScript.Echo objPnP.Manufacturer 'производитель
' 	WScript.Echo objPnP.PNPDeviceID 'идентификатор логического устройства
' 	WScript.Echo
' Next