   M S B A M L   `   `   `  ����E  ATurMachine, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null'clr-namespace:TurMachine
TurMachine  5   	       TurMachine.MainWindow   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   *localclr-namespace:TurMachine     5   	     � 
ResizeMode$  NoResize=�5   	    � Title$ Turing machine emulator��5	   	   $	��300��6)   $	��600��66   .��5
      �  � ColumnDefinitions 5   
   �� 5      $��1* �6   �� 5      $��1* �6    � RowDefinitions 5   
   �� 5      $��1* �6   �� 5      $��4* �6   �� 5      $��2* �6   .+�5   
   �� -   5        $��	FileInput��5      $��Ввод из файла��6"   $��Center=�6:   $��	95,5,95,5q�6X   $��Center=�6k   $��25��6�   $	��100��6�   6�   �� 5   
   -   5        $��rulesWindow��5      $��Center=�6%   $��1��6B   $	��140��6O   $��Center=�6\   $	��244��6w   $
��24,0q�6�   $��14(�6�   ��5      �� 5      .R�5      � $	��0,2q�6   .+�5      �� ��6$   �� *LineOfTable+5      5      5      �� 5"   
    �� Orientation$ 
Horizontal=�6   $��2��6.   $��26,26,24,26q�6;   .+�5#      �� -   5        $��	Next_step��5#      $��	Next step��6&   $��33,0,0,0q�6:   $��74��6L   6W   �� 5$      -   5        $��Complete_computing��5$      $��Complete��6/   $��33,0,0,0q�6B   $��74��6T   6_   5%      �� 5'   
   -   5        $��label��5'      $��Шаги��6   $
��Bold"�6,   $��18(�6>   $��1��6L   $��Center=�6\   $��115,-5,115,10q�6y   $��Bottom=�6�   �� 5)   
   -   5        $��stepsBox��5)      $��1��6"   $��
10,5,10,10q�62   $��1��6F   $��2��6S   �� 5+   
   -   5        $��label1��5+      $7��1# | New state | Cur. sym. |                 Strip��6   $
��Left=�6Z   $	��Top=�6u   $��1��6�   $��	10,20,0,0q�6�   $��2��6�   $	��277��6�   5,      5-      