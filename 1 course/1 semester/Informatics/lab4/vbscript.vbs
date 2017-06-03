Set objArgs = WScript.Arguments

Dim i 
Dim j 
Dim t 
Dim numberOfLines 
Dim numberOfColumns 
Dim Table1 
Dim xmlFile
set xmlFile = CreateObject("Microsoft.XMLDOM")
xmlFile.Async = "False"
If (xmlFile.Load (objArgs(0))) Then
	Set word = CreateObject("Word.Application")
	Dim FSO
	Dim path
	Set FSO = CreateObject("Scripting.FileSystemObject")
	path = FSO.GetParentFolderName(WScript.ScriptFullName)
	Set wordDoc = word.Documents.Add()
	wordDoc.activate
	
	i = 1
	j = 0
	numberOfLines = 3
	numberOfColumns = 4
	
	Set colNodes = xmlFile.selectNodes("/pokemons/species/*")
	
	Set Range1 = wordDoc.Paragraphs(1).Range 
	Set Table1 = wordDoc.Tables.Add(Range1, numberOfLines, numberOfColumns)
	
	For Each objNode in colNodes
		j = j + 1
		Table1.Cell(i,j).Range.Text = objNode.Text
		If (j = 4) Then
			 	i = i + 1 
			 	j = 0
		End If
	Next
	
	wordDoc.SaveAs (path & "\docWithXmlData")
	word.quit
Else
	MsgBox "Error"
End If

' cscript vbscript.vbs "pokemons_for_vba.xml" 
