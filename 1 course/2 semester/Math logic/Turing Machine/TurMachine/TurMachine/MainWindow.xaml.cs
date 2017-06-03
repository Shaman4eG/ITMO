using System.Text.RegularExpressions;
using System.Windows;
using System.Collections.Generic;


namespace TurMachine
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {   
        public static int NumOfStates { get; set; }
        private static char[] alphabet = new char[4];
        public static int SymsAlreadyInAlphabet { get; set; } = 0;
        private static string rulesInput;
        private static char[] pseudoInfiniteStrip = new char[1100];
        private int CounterOfSymbols { get; set; } = 0;
        private int MaxNumOfIterations = 499;
        private bool InputDoneSuccessfully = false;


        public MainWindow()
        {
            InitializeComponent();
        }

        private void FileInput_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.Filter = "Text files(*.txt)|*.txt";
            
            if (dlg.ShowDialog() == true)
            {
                string inputText= System.IO.File.ReadAllText(dlg.FileName);
                FileInputCheckAndInfoVisualisation(inputText);
            }
            else
                MessageBox.Show("Error trying open dialog box or file was not chosen.", "Input error", MessageBoxButton.OK, MessageBoxImage.Error);

        }

        public bool FileInputCheckAndInfoVisualisation(string inputText)
        {
            int currSymIndex = 0;
            int minNumberOfSymsInInput = 12;
            CleanInputData();   // Стираем прошлый ввод
            if (inputText.Length >= minNumberOfSymsInInput)
            {
                if (CheckNumOfStatesInput(inputText, ref currSymIndex))
                    if (CheckAlphabetInput(inputText, ref currSymIndex))
                        if (CheckRulesInput(inputText, ref currSymIndex))
                            if (CheckInitialDataInput(inputText, ref currSymIndex))
                            {
                                inputRulesInTable();
                                InputDoneSuccessfully = true;
                                return true;
                            }
            }
            else
                MessageBox.Show("Invalid data input.", "Input error", MessageBoxButton.OK, MessageBoxImage.Error);

            return false;
        }

        private void CleanInputData()
        {
            for (int i = 0; i < alphabet.Length; i++)
                alphabet[i] = default(char);

            steps.Clear();

            SymsAlreadyInAlphabet = 0;

            CurrStepNum = 0;

            NumOfIterations = 0;
            CurrState = 1;
            CurrStripIndex = 500;
            Completed = false;

            lowerShowBoundKeeper = 499;
            upperShowBoundKeeper = 0;
            upperShowBoundKeeperNotInitialized = true;
        }

        private static bool CheckNumOfStatesInput(string inputText, ref int currSymIndex)
        {
            if (checkIfNumAndValid(inputText[currSymIndex++]))
                NumOfStates = inputText[currSymIndex - 1] - '0';
            else
            {
                MessageBox.Show("Invalid number of states input.", "Input error", MessageBoxButton.OK, MessageBoxImage.Error);
                return false;
            }

            if ((currSymIndex == inputText.Length) || (inputText[currSymIndex] != '\r'))
            {
                MessageBox.Show("Invalid number of states input.", "Input error", MessageBoxButton.OK, MessageBoxImage.Error);
                return false;
            }

            currSymIndex += 2;
            return true;
        }

        private static bool checkIfNumAndValid(char currSym)
        {
            int currSymInt;
            bool isNum;

            do  // Повторять, пока не будет получен валидный ввод
            {
                isNum = int.TryParse(currSym.ToString(), out currSymInt);   // Проверяем, что ввели число
                if (!isNum)
                    return false;
                else if ((currSymInt < 1) || (currSymInt > 4))  // Проверяем, что введенное число находится в диапозоне 1-4
                    return false;
            }
            while (false);
            return true;
        }

        private static bool CheckAlphabetInput(string inputText, ref int currSymIndex)
        {
            string alphabetInput = null;
            while ((currSymIndex < inputText.Length) && (inputText[currSymIndex] != '\r'))
                alphabetInput += inputText[currSymIndex++];
            if (currSymIndex == inputText.Length)
            {
                MessageBox.Show("Invalid alphabet input.", "Input error", MessageBoxButton.OK, MessageBoxImage.Error);
                return false;
            }

            if ((alphabetInput != null) && (Regex.IsMatch(alphabetInput, @"^(.\s){0,3}.$")))
            {
                int j = 0;
                for (int i = 0; i < alphabetInput.Length; i += 2)
                {
                    alphabet[j++] = alphabetInput[i];
                    SymsAlreadyInAlphabet++;
                }
            }
            else
            {
                MessageBox.Show("Invalid alphabet input.", "Input error", MessageBoxButton.OK, MessageBoxImage.Error);
                return false;
            }

            currSymIndex += 2;
            if (CheckAlphabetAppropriateness(SymsAlreadyInAlphabet))
                return true;
            else
                return false;
        }

        private static bool CheckAlphabetAppropriateness(int SymsAlreadyInAlphabet)
        {
            bool symSExists = false;
            if (alphabet[0] == 'S')
                symSExists = true;
            for (int i = 0; i < SymsAlreadyInAlphabet - 1; i++)
                for (int j = i + 1; j < SymsAlreadyInAlphabet; j++)
                {
                    if (alphabet[i].Equals(alphabet[j]))
                    {
                        MessageBox.Show("Invalid alphabet input. Same symbols exist.", "Input error", MessageBoxButton.OK, MessageBoxImage.Error);
                        return false;
                    }
                    else if ((alphabet[i] == 'S') || (alphabet[j] == 'S'))
                        symSExists = true;
                }
            if (symSExists)
                return true;
            else
            {
                MessageBox.Show("No 'S' symbol in alphabet.", "Input error", MessageBoxButton.OK, MessageBoxImage.Error);
                return false;
            }
        }

        private bool CheckRulesInput(string inputText, ref int currSymIndex)
        {
            int rulesLineStartIndex = currSymIndex;
            bool foundMatch;
            rulesInput = null;
            int i;
            int numOfRules = SymsAlreadyInAlphabet * NumOfStates;

            for (i = currSymIndex; i < 5 * numOfRules - 1 + currSymIndex; i++)    // '5' - четыре составляющие правила (Например: q01L) и пробел. '- 1' - минус пробел у последнего правила.
            {
                if (i < inputText.Length)
                {
                    if (inputText[i] != '\r')
                        rulesInput += inputText[i];
                    else
                    {
                        MessageBox.Show("Invalid rules input.", "Input error", MessageBoxButton.OK, MessageBoxImage.Error);
                        return false;
                    }
                }
                else
                {
                    MessageBox.Show("Invalid rules input.", "Input error", MessageBoxButton.OK, MessageBoxImage.Error);
                    return false;
                }
            }

            currSymIndex += 2;
            if ((i < inputText.Length) && (inputText[i] == '\r') && (Regex.IsMatch(rulesInput, @"^(q[0-4].[LCR]\s{1}){0,15}(q[0-4].[LCR])$")))
            {
                for (int j = 0; j < numOfRules; j++)
                {
                    foundMatch = false;
                    for (int k = 0; k < SymsAlreadyInAlphabet; k++)
                        if (alphabet[k] == inputText[currSymIndex])
                        {
                            foundMatch = true;
                            currSymIndex += 5;
                            k = 5;
                        }
                    if (!foundMatch)
                    {
                        MessageBox.Show("Not all symbols in rules are in alphabet.", "Input error", MessageBoxButton.OK, MessageBoxImage.Error);
                        return false;
                    }
                }
            }
            else
            {
                MessageBox.Show("Invalid rules input.", "Input error", MessageBoxButton.OK, MessageBoxImage.Error);
                return false;
            }

            currSymIndex = rulesLineStartIndex + 1;
            for (int j = 0; j < numOfRules; j++)
            {
                if (inputText[currSymIndex] - '0' <= NumOfStates)
                    currSymIndex += 5;
                else
                {
                    MessageBox.Show("Invalid state number in rules.", "Input error", MessageBoxButton.OK, MessageBoxImage.Error);
                    return false;
                }
            }
            return true;
        }

        private string initialDataInput;

        private bool CheckInitialDataInput(string inputText, ref int currSymIndex)
        {
            initialDataInput = null;
            CounterOfSymbols = 0;
            while ((currSymIndex < inputText.Length) && (CounterOfSymbols < 100))
            {
                initialDataInput += inputText[currSymIndex++];
                CounterOfSymbols++;
            }

            for (int i = 0; i < 1100; i++)
                pseudoInfiniteStrip[i] = 'S';

            bool foundMatch;
            if (currSymIndex < inputText.Length)
            {
                MessageBox.Show("Invalid initial data input.", "Input error", MessageBoxButton.OK, MessageBoxImage.Error);
                return false;
            }
            else if (initialDataInput == null)
                return true;
            else if (!Regex.IsMatch(initialDataInput, @"^(\w{1}){0,100}$"))
            {
                MessageBox.Show("Invalid initial data input.", "Input error", MessageBoxButton.OK, MessageBoxImage.Error);
                return false;
            }
            else
            {
                for (int i = 0; i < CounterOfSymbols; i++)
                {
                    foundMatch = false;
                    for (int j = 0; j < SymsAlreadyInAlphabet; j++)
                        if (initialDataInput[i] == alphabet[j])
                        {
                            foundMatch = true;
                            j = 5;
                        }
                    if (!foundMatch)
                    {
                        MessageBox.Show("Not all symbols in initial input are in alphabet.", "Input error", MessageBoxButton.OK, MessageBoxImage.Error);
                        return false;
                    }
                    else
                        pseudoInfiniteStrip[i + 500] = initialDataInput[i];
                }
            }

            return true;
        }

        private void inputRulesInTable()
        {
            string[] linesOfRules = new string[5];
            int j = 0;
            int previousJ = 0;
            int numOfIterationsNeeded = SymsAlreadyInAlphabet * 5 - 1;
            int i;

            for (i = 0; i < NumOfStates + 1; i++)
                switch (i)
                {
                    case 0:
                        linesOfRules[i] = "         ";

                        for (; j < SymsAlreadyInAlphabet; j++)
                            linesOfRules[i] += alphabet[j] + "       ";
                        if (j < 5)
                            for (; j < 5; j++)
                                linesOfRules[i] += "         ";
                        break;

                    case 1:
                        linesOfRules[i] = "q1| ";
                        for (j = 0; j < numOfIterationsNeeded; j++)
                            linesOfRules[i] += rulesInput[j];
                        break;

                    case 2:
                        linesOfRules[i] = "q2|";
                        previousJ = j;
                        numOfIterationsNeeded += j + 1;
                        for (; j < numOfIterationsNeeded; j++)
                            linesOfRules[i] += rulesInput[j];
                        previousJ = j - previousJ;
                        break;

                    case 3:
                        linesOfRules[i] = "q3|";
                        numOfIterationsNeeded += previousJ;
                        previousJ = j;
                        for (; j < numOfIterationsNeeded; j++)
                            linesOfRules[i] += rulesInput[j];
                        previousJ = j - previousJ;
                        break;

                    case 4:
                        linesOfRules[i] = "q4|";
                        numOfIterationsNeeded += previousJ;
                        for (; j < numOfIterationsNeeded; j++)
                            linesOfRules[i] += rulesInput[j];
                        break;
                }

            List<Rules> rulesForSending = new List<Rules>();
            for (j = 0; j < i; j++)
                rulesForSending.Add(new Rules(linesOfRules[j]));

            rulesWindow.ItemsSource = rulesForSending;
            GetStepsInfo();
        }

        private int CurrStepNum { get; set; } = 0;

        private List<string> steps = new List<string>();

        private int lowerShowBoundKeeper = 499;
        private int upperShowBoundKeeper = 0;
        private bool upperShowBoundKeeperNotInitialized = true;

        private void GetStepsInfo()
        {
            string newInitialInput = null;

            if (lowerShowBoundKeeper + 1 > CurrStripIndex)
                lowerShowBoundKeeper = CurrStripIndex - 1;

            if (upperShowBoundKeeperNotInitialized)
            {
                upperShowBoundKeeper = 500 + CounterOfSymbols + 1;
                upperShowBoundKeeperNotInitialized = false;
            }

            if (upperShowBoundKeeper - 2 < CurrStripIndex)
                upperShowBoundKeeper = CurrStripIndex + 2;

            for (int i = lowerShowBoundKeeper; i < upperShowBoundKeeper; i++)
                newInitialInput += pseudoInfiniteStrip[i];
            string stepsString = CurrStepNum++ + " |        " + CurrState + "        |       " + (CurrStripIndex - 500) + "       | " + newInitialInput;
            steps.Add(stepsString);
            InputStepsInfo(steps);
        }

        class Rules
        {
            public string LineOfTable { get; set; }

            public Rules(string line)
            {
                LineOfTable = line;
            }
        }

        private bool Completed { get; set; } = false;

        private void Complete_computing_Click(object sender, RoutedEventArgs e)
        {
            if (!Completed) 
            {
                if (InputDoneSuccessfully == true)
                {
                    if ((Action(true) && (Completed == true)))
                        MessageBox.Show("Computing finished!", "Result", MessageBoxButton.OK, MessageBoxImage.Information);
                    else
                    {
                        Completed = true;
                        MessageBox.Show("Unable to solve the problem for " + MaxNumOfIterations + " actions.", "Result", MessageBoxButton.OK, MessageBoxImage.Error);
                    }
                }
                else
                    MessageBox.Show("Input not found.", "Result", MessageBoxButton.OK, MessageBoxImage.Error);
            }
            else
                MessageBox.Show("Unable to continue computing.", "Result", MessageBoxButton.OK, MessageBoxImage.Exclamation);
        }

        private void Next_step_Click(object sender, RoutedEventArgs e)
        {
            if (!Completed)
            {
                if (InputDoneSuccessfully == true)
                {
                    if (Action(false) && (CurrState == 0) && (Completed == true))
                        MessageBox.Show("Computing completed!", "Result", MessageBoxButton.OK, MessageBoxImage.Information);
                    else if (NumOfIterations == MaxNumOfIterations)
                    {
                        Completed = true;
                        MessageBox.Show("Unable to solve the problem for " + MaxNumOfIterations + " actions.", "Result", MessageBoxButton.OK, MessageBoxImage.Error);
                    }
                }
                else
                {
                    MessageBox.Show("Input not found.", "Result", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
            else
                MessageBox.Show("Unable to continue computing.", "Result", MessageBoxButton.OK, MessageBoxImage.Exclamation);
        }

        private int NumOfIterations { get; set; } = 0;
        private int CurrState { get; set; } = 1;
        private int CurrStripIndex { get; set; } = 500;

        private bool Action(bool fullComplete)
        {
            do
            {
                int symPositionInAlphabet = 0;
                for (int j = 0; j < SymsAlreadyInAlphabet; j++)
                    if (pseudoInfiniteStrip[CurrStripIndex] == alphabet[j])
                    {
                        symPositionInAlphabet = j;
                        j = 5;
                    }

                int currInRulesIndex = 1 + 5 * ((CurrState - 1) * SymsAlreadyInAlphabet + symPositionInAlphabet);
                CurrState = rulesInput[currInRulesIndex++] - '0';
                pseudoInfiniteStrip[CurrStripIndex] = rulesInput[currInRulesIndex++];
                switch (rulesInput[currInRulesIndex])
                {
                    case 'L':
                        CurrStripIndex--;
                        break;

                    case 'R':
                        CurrStripIndex++;
                        break;
                }

                GetStepsInfo();

                if (CurrState == 0)
                {
                    Completed = true;
                    return true;
                }

                NumOfIterations++;
            }
            while ((fullComplete) && (NumOfIterations < MaxNumOfIterations));

            if (!fullComplete)
            {
                if (NumOfIterations < MaxNumOfIterations)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }

        private void InputStepsInfo(List<string> steps)
        {
            stepsBox.ItemsSource = null;
            stepsBox.ItemsSource = steps; 
        }

    }
}  




