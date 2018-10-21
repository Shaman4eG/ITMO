using System.Threading;
using NUnit.Framework;
using OpenQA.Selenium;
using OpenQA.Selenium.Chrome;

using static SWT.Lab1.ConstantsForTesting;

namespace SWT.Lab1
{
    public class Tests
    {
        IWebDriver _driver;

        [SetUp]
        public void StartBrowser()
        {
            _driver = new ChromeDriver(ChromeExeDirectory);
        }

        [Test]
        public void TumblerFunctionality()
        {
            _driver.Url = WebsiteUrl;
            Login();



            Thread.Sleep(3000);
        }

        private void Login()
        {
            IWebElement loginButton = _driver.FindElement(By.XPath(LoginButtonPath));
            loginButton.Click();

            IWebElement emailTextField = _driver.FindElement(By.XPath(EmailTextFieldPath));
            emailTextField.SendKeys(Email);

            IWebElement confirmEmailButton = _driver.FindElement(By.XPath(SubmitButtonPath));
            confirmEmailButton.Click();

            Thread.Sleep(1500);

            IWebElement usePasswordButton = _driver.FindElement(By.XPath(UsePasswordButtonPath));
            usePasswordButton.Click();

            IWebElement passwordTextField = _driver.FindElement(By.XPath(PasswordTextFieldPath));
            passwordTextField.SendKeys(Password);

            IWebElement confirmPasswordButton = _driver.FindElement(By.XPath(SubmitButtonPath));
            confirmPasswordButton.Click();
        }

        [TearDown]
        public void CloseBrowser()
        {
            _driver.Close();
        }
    }
}
