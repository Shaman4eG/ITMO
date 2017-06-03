using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Text.RegularExpressions;
using System.Globalization;

namespace CompMathLab1
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private static DataKeeper dataKeeper;
        private const int maxIterations = 500;
        private const int RandomMinNumber = -100;
        private const int RandomMaxNumber = 100;

        public MainWindow()
        {
            InitializeComponent();
            // Needed to think of '.' as a floating point number delimet instead of ','.
            CultureInfo.DefaultThreadCurrentCulture = CultureInfo.CreateSpecificCulture("en-US");
        }

        // Opens file dialog. Allows choosing *.txt files. 
        // If success: retrieves data from file to string and calls FileInputCheckAndInfoVisualisation method.
        // If fail: than means user has closed file dialog without choosing a file. No reaction.
        private void InputFromFile_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.Filter = "Text files(*.txt)|*.txt";

            var hasOpenedFile = (bool)dlg.ShowDialog();
            if (hasOpenedFile)
            { 
                string inputText = System.IO.File.ReadAllText(dlg.FileName);
                var fileInputChecker = new FileInputsChecker();
                fileInputChecker.FileInputCheckAndInputVisualisation(inputText, StackPanelForCoefficientsTextBoxes,
                                                                    NumberOfLinearSystemRowsInput, ErroInput);
            }
            dlg = null;
        }

        private void GenerateRandomCoefficients_Click(object sender, RoutedEventArgs e)
        {
            if ((dataKeeper == null) || (dataKeeper.NumberOfLinearSystemRows == -1))
            {
                MessageBox.Show("СЛАУ не создана.", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            Random randomNumber = new Random();
            StringBuilder coefficients = new StringBuilder(4200);
            int numberOfTextBoxes = dataKeeper.NumberOfLinearSystemRows * dataKeeper.NumberOfLinearSystemRows 
                                    + dataKeeper.NumberOfLinearSystemRows;
            int diagonalElement = 0;
            for (int i = 0; i < numberOfTextBoxes; i++)
            {
                if (i == diagonalElement)
                {
                    diagonalElement += dataKeeper.NumberOfLinearSystemRows + 2;
                    coefficients.Append(Math.Round((randomNumber.NextDouble() * (RandomMaxNumber * 100) + RandomMinNumber * 100), 4));
                    coefficients.Append(' ');
                    continue;
                }
                coefficients.Append(Math.Round((randomNumber.NextDouble() * (RandomMaxNumber - RandomMinNumber) + RandomMinNumber), 4));
                coefficients.Append(' ');
            }

            var inputerOfTextBoxValue = new FileInputsChecker();
            inputerOfTextBoxValue.CheckCoefficientsInputAndSetTextBoxesValues(coefficients.ToString());
        }

        // Checks linear system size input. Saves data. Creates TextBoxes for coefficients.
        private void GenerateCoefficientsTextBoxes_Click(object sender, RoutedEventArgs e)
        {
            var sizeChecker = new InputsChecker();
            var textBoxesCreator = new TextBoxesCreator();
            dataKeeper = new DataKeeper();

            // Check linear system size input. If -1 returned - invalid input.
            int numberOfLinearSystemRows = sizeChecker.СheckLinearSystemSizeInput(NumberOfLinearSystemRowsInput.Text);
            if (numberOfLinearSystemRows == -1) return;

            // Saving data.
            dataKeeper.NumberOfLinearSystemRows = numberOfLinearSystemRows;

            // Creating TextBoxes, showing them in GUI and saving data.
            textBoxesCreator.CreateTextBoxesForCoefficients(StackPanelForCoefficientsTextBoxes, numberOfLinearSystemRows);
        }

        private void SolveLinearSystem_Click(object sender, RoutedEventArgs e)
        {
            var inputsChecker = new InputsChecker();
            
            // Checks
            bool wereCreated = inputsChecker.CheckCoefficientsTextBoxexWereCreated();
            if (!wereCreated) return;

            decimal errorInput = inputsChecker.СheckErrorInput(ErroInput.Text);
            if (errorInput == -1) return;

            // Saving data
            dataKeeper.ErrorInput = errorInput;

            // Check coefficients TextBoxes values and put right side values in valuesOfLinearSystemRightSide and
            // left side values in valuesOfLinearSystemLeftSide.
            decimal[] valuesOfLinearSystemRightSide = new decimal[20];
            decimal[,] valuesOfLinearSystemLeftSide = new decimal[20,20];
            int numberOfRows = dataKeeper.NumberOfLinearSystemRows;
            int textBoxIndex = 0;
            int rightSideIndex = 0;
            for (int i = 0; i < numberOfRows; i++)
            {
                for (int j = 0; j <= numberOfRows; j++)
                {
                    textBoxIndex = i * (numberOfRows + 1) + j;
                    if (!Regex.IsMatch(dataKeeper.TextBoxList[textBoxIndex].Text, @"^-?\d{1,8}\.\d{1,16}$|^-?[0-9]{1,8}$"))
                    {
                        MessageBox.Show("Неверный ввод коэффициентов системы уравнений.", "Ошибка ввода",
                                         MessageBoxButton.OK, MessageBoxImage.Error);
                        return;
                    }

                    rightSideIndex = i * (numberOfRows + 1) + numberOfRows;
                    if (rightSideIndex == textBoxIndex)
                    {
                        valuesOfLinearSystemRightSide[i] = (Convert.ToDecimal(dataKeeper.TextBoxList[textBoxIndex].Text));
                    }
                    else
                    {
                        valuesOfLinearSystemLeftSide[i,j] = (Convert.ToDecimal(dataKeeper.TextBoxList[textBoxIndex].Text));
                    }
                }
            }

            // Cleaning old data.
            TableForOutput.Deltas.Clear();
            TableForOutput.ActualNumberOfIterations = 0;
            OutputTableGrid.Columns.Clear();
            // Compute
            bool computedSuccessfully = GaussSeidelMethod.GaussSeidelMethodThreshold(errorInput, maxIterations, 
                                                                                     valuesOfLinearSystemLeftSide, 
                                                                                     valuesOfLinearSystemRightSide, 
                                                                                     dataKeeper.NumberOfLinearSystemRows);
            if (!computedSuccessfully) return;

            // Setting output values fractional part to have same number of digits after '.' as error has.
            string errorInputStr = dataKeeper.ErrorInput.ToString();
            int numberOfFractalDigitsInError = 4;
            int currentErrorDigitndex = 0;
            while ((currentErrorDigitndex < errorInputStr.Length) && (errorInputStr[currentErrorDigitndex] != '.'))
            {
                currentErrorDigitndex++;
            }
            if (currentErrorDigitndex != errorInputStr.Length)
            {
                numberOfFractalDigitsInError = 0;
            }
            currentErrorDigitndex++;

            for (; currentErrorDigitndex < ErroInput.Text.Length; currentErrorDigitndex++)
            {
                numberOfFractalDigitsInError++;
            }

            // Output
            TableForOutput.Output(OutputTable, OutputTableGrid, dataKeeper.NumberOfLinearSystemRows, numberOfFractalDigitsInError);

            // Result message
            if (GaussSeidelMethod.Converges)
            {
                MessageBox.Show("СЛАУ сходится. Количество итераций: " + (TableForOutput.ActualNumberOfIterations), 
                                "Результат", MessageBoxButton.OK, MessageBoxImage.Information);
            }
            else
            {
                MessageBox.Show("СЛАУ расходится. Количество итераций: " + (TableForOutput.ActualNumberOfIterations), 
                                "Результат", MessageBoxButton.OK, MessageBoxImage.Information); ;
            }
        }


        internal class DataKeeper
        {
            internal int NumberOfLinearSystemRows { get; set; }
            internal decimal ErrorInput { get; set; }
            internal List<StackPanel> ListOfStackPanels { get; set; }
            internal List<TextBox> TextBoxList { get; set; }
        }

        internal class FileInputsChecker
        {
            internal bool FileInputCheckAndInputVisualisation(string inputText, StackPanel StackPanelForCoefficientsTextBoxes,
                                                             TextBox NumberOfLinearSystemRowsInput, TextBox ErroInput)
            {
                int currentSymbolIndex = 0;
                string partOfInputStringKeeper = "";

                // Создаем подстроку, содержащию только размерность СЛАУ
                while (currentSymbolIndex < inputText.Length)
                {
                    if (inputText[currentSymbolIndex] == '\r')
                    {
                        break;
                    }
                    partOfInputStringKeeper += inputText[currentSymbolIndex++];
                }
                // Проверяем, что файл не закончен, иначе выводим ошибку
                if (currentSymbolIndex == inputText.Length)
                {
                    MessageBox.Show("Не задана погрешность.", "Ошибка ввода из файла", 
                                     MessageBoxButton.OK, MessageBoxImage.Error);
                    return false;
                }
                // Проверяем правильности ввода
                else if (!CheckNumberOfLinearSystemRowsInput(partOfInputStringKeeper, ref currentSymbolIndex,
                                                                      StackPanelForCoefficientsTextBoxes, 
                                                                      NumberOfLinearSystemRowsInput))
                {
                    return false;
                }
                // Пропускаем символы перевода строки: /r/n
                currentSymbolIndex += 2;

                // Создаем подстроку, содержащию только погрешность
                partOfInputStringKeeper = "";
                while (currentSymbolIndex < inputText.Length)
                {
                    if (inputText[currentSymbolIndex] == '\r')
                    {
                        break;
                    }
                    partOfInputStringKeeper += inputText[currentSymbolIndex++];
                }
                // Проверяем, что файл не закончен, иначе выводим ошибку
                if (currentSymbolIndex == inputText.Length)
                {
                    MessageBox.Show("Не заданы коэффициенты при иксах.", "Ошибка ввода из файла", 
                                     MessageBoxButton.OK, MessageBoxImage.Error);
                    return false;
                }
                // Проверяем правильности ввода
                else if (!CheckErrorInput(partOfInputStringKeeper, ref currentSymbolIndex, ErroInput))
                {
                    return false;
                }
                // Пропускаем символы перевода строки: /r/n
                currentSymbolIndex += 2;

                // Создаем подстроку, содержащию только коэффициенты при иксах
                partOfInputStringKeeper = "";
                int numberOfTextBoxes = dataKeeper.NumberOfLinearSystemRows * dataKeeper.NumberOfLinearSystemRows
                                        + dataKeeper.NumberOfLinearSystemRows;
                for (int i = 0; i < numberOfTextBoxes; i++)
                {
                    while (currentSymbolIndex < inputText.Length)
                    {
                        partOfInputStringKeeper += inputText[currentSymbolIndex++];
                        if (inputText[currentSymbolIndex - 1] == ' ')
                        {
                            break;
                        }
                    }
                    if ((currentSymbolIndex == inputText.Length) && (i != numberOfTextBoxes - 1))
                    {
                        MessageBox.Show("Заданы не все коэффициенты при иксах.", "Ошибка ввода из файла", MessageBoxButton.OK, MessageBoxImage.Error);
                        return false;
                    }
                }
                partOfInputStringKeeper += ' ';
                // Проверяем, что файл закончен, иначе выводим ошибку
                if (currentSymbolIndex != inputText.Length)
                {
                    MessageBox.Show("Неверный ввод коэффициентов при иксах.", "Ошибка ввода из файла", 
                                     MessageBoxButton.OK, MessageBoxImage.Error);
                    return false;
                }
                
                // Проверяем правильности ввода коэффициентов при иксах и записываем их TextBoxes.
                if (!CheckCoefficientsInputAndSetTextBoxesValues(partOfInputStringKeeper))
                {
                    return false;
                }

                return true;
            }

            private bool CheckNumberOfLinearSystemRowsInput(string numberOfLinearSystemRowsInput, ref int currentSymbolIndex,
                                                                     StackPanel StackPanelForCoefficientsTextBoxes, 
                                                                     TextBox NumberOfLinearSystemRowsInput)
            {
                var sizeChecker = new InputsChecker();
                var textBoxesCreator = new TextBoxesCreator();
                dataKeeper = new DataKeeper();

                // Check linear system size input. If -1 returned - invalid input.
                int numberOfLinearSystemRows = sizeChecker.СheckLinearSystemSizeInput(numberOfLinearSystemRowsInput);
                if (numberOfLinearSystemRows == -1) return false;

                // Saving data.
                dataKeeper.NumberOfLinearSystemRows = numberOfLinearSystemRows;

                // Creating TextBoxes, showing them in GUI and saving data.
                textBoxesCreator.CreateTextBoxesForCoefficients(StackPanelForCoefficientsTextBoxes, numberOfLinearSystemRows);

                NumberOfLinearSystemRowsInput.Text = numberOfLinearSystemRowsInput;
                return true;
            }

            private bool CheckErrorInput(string error, ref int currentSymbolIndex, TextBox ErroInput)
            {
                var inputsChecker = new InputsChecker();

                decimal errorInput = inputsChecker.СheckErrorInput(error);
                if (errorInput == -1) return false;

                // Saving data
                dataKeeper.ErrorInput = errorInput;
                ErroInput.Text = error;

                return true;
            }

            internal bool CheckCoefficientsInputAndSetTextBoxesValues(string coefficients)
            {
                decimal[] valuesOfLinearSystemRightSide = new decimal[20];
                decimal[,] valuesOfLinearSystemLeftSide = new decimal[20, 20];
                int numberOfRows = dataKeeper.NumberOfLinearSystemRows;
                int textBoxIndex = 0;
                int rightSideIndex = 0;
                int symbolIndex = 0;
                StringBuilder textForTextBox = new StringBuilder(30);
                for (int i = 0; i < numberOfRows; i++)
                {
                    for (int j = 0; j <= numberOfRows; j++)
                    {
                        for (; coefficients[symbolIndex] != ' '; symbolIndex++)
                        {
                            textForTextBox.Append(coefficients[symbolIndex]);
                        }
                        symbolIndex++;

                        textBoxIndex = i * (numberOfRows + 1) + j;
                        if (!Regex.IsMatch(textForTextBox.ToString(), @"^-?\d{1,8}\.\d{1,16}$|^-?[0-9]{1,8}$"))
                        {
                            MessageBox.Show("Неверный ввод коэффициентов системы уравнений.", "Ошибка ввода из файла", 
                                             MessageBoxButton.OK, MessageBoxImage.Error);
                            return false;
                        }
                        dataKeeper.TextBoxList[textBoxIndex].Text = textForTextBox.ToString();
                        textForTextBox.Clear();

                        rightSideIndex = i * (numberOfRows + 1) + numberOfRows;
                        if (rightSideIndex == textBoxIndex)
                        {
                            valuesOfLinearSystemRightSide[i] = (Convert.ToDecimal(dataKeeper.TextBoxList[textBoxIndex].Text));
                        }
                        else
                        {
                            valuesOfLinearSystemLeftSide[i, j] = (Convert.ToDecimal(dataKeeper.TextBoxList[textBoxIndex].Text));
                        }
                    }
                }

                return true;
            }
        }

        // Checks input of linear system size, error, existens.
        internal class InputsChecker
        {
            // If success: returns input linear system size.
            // If fail: outputs error message and returns -1.
            internal int СheckLinearSystemSizeInput(string numberOfLinearSystemRows)
            {
                if (!Regex.IsMatch(numberOfLinearSystemRows, @"^[2-9]$|^1\d$|^20$"))
                {
                    MessageBox.Show("Неверный ввод размерности.", "Ошибка ввода", MessageBoxButton.OK, MessageBoxImage.Error);
                    return -1;
                }

                return Convert.ToInt32(numberOfLinearSystemRows);
            }

            // If success: returns input error.
            // If fail: outputs error message and returns -1.
            internal decimal СheckErrorInput(string errorInput)
            {
                if (!Regex.IsMatch(errorInput, @"^\d{1,8}\.\d{1,16}$|^[1-9]{1,8}$"))
                {
                    MessageBox.Show("Неверный ввод погрешности.", "Ошибка ввода", MessageBoxButton.OK, MessageBoxImage.Error);
                    return -1;
                }

                return Convert.ToDecimal(errorInput);
            }

            // If success: returns true.
            // If fail: outputs error message and returns false.
            internal bool CheckCoefficientsTextBoxexWereCreated()
            {
                if ((dataKeeper == null) || (dataKeeper.NumberOfLinearSystemRows == -1))
                {
                    MessageBox.Show("СЛАУ не создана.", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
                    return false;
                }

                return true;
            }
        }

        internal class TextBoxesCreator
        {
            internal List<StackPanel> ListOfStackPanels { get; set; } = new List<StackPanel>();
            internal List<TextBox> TextBoxList { get; set; } = new List<TextBox>();

            // Creating TextBoxes, showing them in GUI and saving data.
            internal void CreateTextBoxesForCoefficients(StackPanel StackPanelForCoefficientsTextBoxes, int numberOfLinearSystemRows)
            {
                // Deleting previous TextBoxes rows.
                StackPanelForCoefficientsTextBoxes.Children.Clear();

                // Each row of TextBoxes will be put in a separate StackPanel.
                for (int i = 0; i < numberOfLinearSystemRows; i++)
                {
                    StackPanel row = new StackPanel();
                    row.Orientation = Orientation.Horizontal;
                    ListOfStackPanels.Add(row);
                }

                // Inner for: creating each linear system left side TextBoxes and "Xi + " symbols, but one.
                // Outer for: adding the last left side elemnt, then " = " and right side TextBox. At the of for
                // end we add filled StackPanel to the defined in XAML "StackPanelForCoefficientsTextBoxes" StackPanel.
                TextBox boxForCoefficient;
                Label xAndItsIndexAndSign;
                for (int rowNumber = 0; rowNumber < numberOfLinearSystemRows; rowNumber++)
                {
                    for (int columnNumber = 0; columnNumber < numberOfLinearSystemRows - 1; columnNumber++)
                    {
                        boxForCoefficient = new TextBox();
                        boxForCoefficient.Width = 60;
                        boxForCoefficient.FontSize = 15;
                        boxForCoefficient.TextAlignment = TextAlignment.Right;
                        ListOfStackPanels[rowNumber].Children.Add(boxForCoefficient);
                        TextBoxList.Add(boxForCoefficient);

                        xAndItsIndexAndSign = new Label();
                        xAndItsIndexAndSign.Content = "x" + (columnNumber + 1) + " + ";
                        xAndItsIndexAndSign.FontSize = 12;
                        ListOfStackPanels[rowNumber].Children.Add(xAndItsIndexAndSign);
                    }
                    boxForCoefficient = new TextBox();
                    boxForCoefficient.Width = 60;
                    boxForCoefficient.FontSize = 15;
                    boxForCoefficient.TextAlignment = TextAlignment.Right;
                    ListOfStackPanels[rowNumber].Children.Add(boxForCoefficient);
                    TextBoxList.Add(boxForCoefficient);

                    xAndItsIndexAndSign = new Label();
                    xAndItsIndexAndSign.Content = "x" + (numberOfLinearSystemRows) + " = ";
                    xAndItsIndexAndSign.FontSize = 12;
                    ListOfStackPanels[rowNumber].Children.Add(xAndItsIndexAndSign);

                    boxForCoefficient = new TextBox();
                    boxForCoefficient.Width = 60;
                    boxForCoefficient.FontSize = 15;
                    ListOfStackPanels[rowNumber].Children.Add(boxForCoefficient);
                    TextBoxList.Add(boxForCoefficient);

                    StackPanelForCoefficientsTextBoxes.Children.Add(ListOfStackPanels[rowNumber]);  // <
                }


                // Saving data to dataKeeper
                dataKeeper.ListOfStackPanels = ListOfStackPanels;
                dataKeeper.TextBoxList = TextBoxList;
            }
        }

        internal static class GaussSeidelMethod
        {
            internal static bool Converges { get; set; }

            internal static bool GaussSeidelMethodThreshold(decimal error, int maxIterations, decimal[,] valuesOfLinearSystemLeftSide,
                                                          decimal[] valuesOfLinearSystemRightSide, int numberOfLinearSystemRows)
            {
                bool noZeros = CheckForZerosInDiagonal(valuesOfLinearSystemLeftSide, numberOfLinearSystemRows);
                if (!noZeros) return false;

                Converges = DiagonalDominance(valuesOfLinearSystemLeftSide, numberOfLinearSystemRows);

                if (Converges)
                {
                    maxIterations *= 10;
                    GaussSeidelMethodRealisation(error, valuesOfLinearSystemLeftSide, maxIterations,
                                                 valuesOfLinearSystemRightSide, numberOfLinearSystemRows);
                }
                else
                {
                    GaussSeidelMethodRealisation(error, valuesOfLinearSystemLeftSide, maxIterations,
                                                 valuesOfLinearSystemRightSide, numberOfLinearSystemRows);
                }

                return true;
            }

            private static bool CheckForZerosInDiagonal(decimal[,] valuesOfLinearSystemLeftSide, int numberOfLinearSystemRows)
            {
                for (int i = 0; i < numberOfLinearSystemRows; i++)
                {
                    if (valuesOfLinearSystemLeftSide[i,i] == 0)
                    {
                        MessageBox.Show("В главной диагонали есть нули.", "Ошибка ввода", 
                                         MessageBoxButton.OK, MessageBoxImage.Information);
                        return false;
                    }
                }

                return true;
            }

            private static bool DiagonalDominance(decimal[,] valuesOfLinearSystemLeftSide, int numberOfLinearSystemRows)
            {
                decimal diagonalElement = 0;
                decimal sumOfRowElementsExceptDiagonal = 0;
                bool diagonalDominanceStrictlyExecuted = false;
                for (int i = 0; i < numberOfLinearSystemRows; i++)
                {
                    diagonalElement = valuesOfLinearSystemLeftSide[i,i];
                    for (int j = 0; j < numberOfLinearSystemRows; j++)
                    {
                        sumOfRowElementsExceptDiagonal += valuesOfLinearSystemLeftSide[i,j];
                    }
                    sumOfRowElementsExceptDiagonal -= diagonalElement;

                    if (sumOfRowElementsExceptDiagonal > diagonalElement) return false;

                    if (sumOfRowElementsExceptDiagonal < diagonalElement) diagonalDominanceStrictlyExecuted = true;
                }

                return diagonalDominanceStrictlyExecuted ? true : false;
            }

            private static void GaussSeidelMethodRealisation(decimal error, decimal[,] valuesOfLinearSystemLeftSide, 
                                                             int maxIterations, decimal[] valuesOfLinearSystemRightSide,
                                                             int totalNumberOfRows)
            {
                int iteration = 1;
                decimal[] approximationsOfUnknowns = new decimal[totalNumberOfRows];
                decimal delta = 0;
                bool overflow = false;

                for (; iteration < maxIterations; iteration++)
                {
                    delta = 0;
                    overflow = computingNewUnknownsApproximations(ref delta, ref approximationsOfUnknowns, iteration,
                                                                  valuesOfLinearSystemLeftSide, overflow,
                                                                  valuesOfLinearSystemRightSide, totalNumberOfRows);
                    if (overflow) return;

                    TableForOutput.Deltas.Add(delta);

                    for (int j = 0; j < totalNumberOfRows; j++)
                    {
                        TableForOutput.CalculatedUnknowns[iteration - 1, j] = approximationsOfUnknowns[j];
                    }

                    if (delta <= error)
                    {
                        TableForOutput.ActualNumberOfIterations = iteration;
                        Converges = true;
                        return;
                    }
                }

                Converges = false;
                TableForOutput.ActualNumberOfIterations = iteration - 1;
            }

            private static bool computingNewUnknownsApproximations(ref decimal delta, ref decimal[] approximationsOfUnknowns,
                                                                   int iteration, decimal[,] valuesOfLinearSystemLeftSide,
                                                                   bool overflow, decimal[] valuesOfLinearSystemRightSide,
                                                                   int totalNumberOfRows)
            {
                int i = 0;
                int j = 0;
                decimal sum = 0;
                decimal newX = 0;
                decimal alpha = 0;
                for (; i < totalNumberOfRows; i++)
                {
                    sum = 0;
                    if (i != 0)
                    {
                        overflow = CountFullSum(ref sum, ref j, i, valuesOfLinearSystemLeftSide,
                                                approximationsOfUnknowns, iteration, totalNumberOfRows,
                                                overflow);
                        if (overflow) return true;
                    }
                    else
                    {
                        j = i + 1;
                        overflow = CountRightSideSum(ref sum, ref j, i, valuesOfLinearSystemLeftSide,
                                                     approximationsOfUnknowns, iteration, totalNumberOfRows);
                        if (overflow) return true;
                    }

                    overflow = ComputeUnknownApproximation(ref sum, ref j, ref newX, i, valuesOfLinearSystemLeftSide,
                                                           valuesOfLinearSystemRightSide, iteration);
                    if (overflow) return true;

                    alpha = Math.Abs(newX - approximationsOfUnknowns[i]);
                    if (delta < alpha) delta = alpha;

                    approximationsOfUnknowns[i] = newX;
                }

                return false;
            }

            private static bool CountFullSum(ref decimal sum, ref int j, int i, decimal[,] valuesOfLinearSystemLeftSide,
                                             decimal[] approximationsOfUnknowns, int iteration, int totalNumberOfRows, 
                                             bool overflow)
            {
                j = 0;
                overflow = CountLeftSideSum(ref sum, ref j, i, valuesOfLinearSystemLeftSide,
                                            approximationsOfUnknowns, iteration);
                if (overflow) return true;

                if (j != totalNumberOfRows - 1)
                {
                    j = i + 1;
                    overflow = CountRightSideSum(ref sum, ref j, i, valuesOfLinearSystemLeftSide,
                                                 approximationsOfUnknowns, iteration, totalNumberOfRows);
                    if (overflow) return true;
                }

                return false;
            }

            private static bool CountLeftSideSum(ref decimal sum, ref int j, int i, decimal[,] valuesOfLinearSystemLeftSide,
                                                 decimal[] approximationsOfUnknowns, int iteration)
            {
                for (; j < i; j++) 
                {
                    try
                    {
                        sum += valuesOfLinearSystemLeftSide[i,j] * approximationsOfUnknowns[j];
                    }
                    catch (OverflowException)
                    {
                        Converges = false;
                        TableForOutput.ActualNumberOfIterations = iteration - 1;
                        return true;
                    }
                    j++;
                }

                return false;
            }

            private static bool CountRightSideSum(ref decimal sum, ref int j, int i, decimal[,] valuesOfLinearSystemLeftSide,
                                                  decimal[] approximationsOfUnknowns, int iteration, int totalNumberOfRows)
            {
                for (; j < totalNumberOfRows; j++)
                {
                    try
                    {
                        sum += valuesOfLinearSystemLeftSide[i,j] * approximationsOfUnknowns[j];
                    }
                    catch (OverflowException)
                    {
                        Converges = false;
                        TableForOutput.ActualNumberOfIterations = iteration - 1;
                        return true;
                    }
                    j++;
                }

                return false;
            }

            private static bool ComputeUnknownApproximation(ref decimal sum, ref int j, ref decimal newX, 
                                                            int i, decimal[,] valuesOfLinearSystemLeftSide,
                                                            decimal[] valuesOfLinearSystemRightSide, int iteration)
            {
                try
                {
                    newX = (valuesOfLinearSystemRightSide[i] - sum) / valuesOfLinearSystemLeftSide[i,i];
                }
                catch (OverflowException)
                {
                    Converges = false;
                    TableForOutput.ActualNumberOfIterations = iteration - 1;
                    return true;
                }

                return false;
            }

        }

        internal class TableForOutput
        {
            internal static List<decimal> Deltas { get; set; } = new List<decimal>();
            internal static int ActualNumberOfIterations { get; set; }
            internal static decimal[,] CalculatedUnknowns { get; set; } = new decimal[5000,20];

            internal static void Output(ListView OutputTable, GridView outputTableGrid, 
                                        int numberOfUnknowns, int numberOfFractalDigitsToOutput)
            {
                GridViewColumn extraColumnForX = new GridViewColumn();
                extraColumnForX.Header = " Iteration № ";
                extraColumnForX.DisplayMemberBinding = new Binding("IterationNumber");
                outputTableGrid.Columns.Add(extraColumnForX);

                extraColumnForX = new GridViewColumn(); 
                extraColumnForX.Header = " Error ";
                extraColumnForX.DisplayMemberBinding = new Binding("Error");
                outputTableGrid.Columns.Add(extraColumnForX);

                for (int i = 1; i <= numberOfUnknowns; i++)
                {
                    extraColumnForX = new GridViewColumn();
                    extraColumnForX.Header = " X" + i + " ";
                    extraColumnForX.DisplayMemberBinding = new Binding("Unknowns[" + (i - 1) + "]"); 
                    outputTableGrid.Columns.Add(extraColumnForX);
                }

                List<ItemForOutput> items = new List<ItemForOutput>();
                ItemForOutput currentItem = new ItemForOutput();
                for (int i = 0; i < ActualNumberOfIterations; i++)
                {
                    currentItem.Unknowns = new decimal[20];

                    currentItem.IterationNumber = i + 1;
                    currentItem.Error = Math.Round(Deltas[i], numberOfFractalDigitsToOutput);
                    for (int j = 0; j < numberOfUnknowns; j++)
                    {
                        currentItem.Unknowns[j] = Math.Round(CalculatedUnknowns[i,j], numberOfFractalDigitsToOutput);
                    }

                    items.Add(currentItem);
                    currentItem = new ItemForOutput();
                }

                OutputTable.ItemsSource = items;
            }
        }

        public class ItemForOutput
        {
            public int IterationNumber { get; set; }
            public decimal Error { get; set; }
            public decimal[] Unknowns { get; set; }
        }
    }
}

