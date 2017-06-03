import org.junit.Test;
import static org.junit.Assert.assertEquals;

public class Test1 {
    
    boolean controlTrue = true;
    boolean controlFalse = false;
    Program3 program = new Program3();
    Program3.inputParCases inputParCases;
    
    
    @Test
    public void testCheckInput() {
        assertEquals(controlTrue, Program3.checkInput("1"));
        assertEquals(controlTrue, Program3.checkInput("0"));
        assertEquals(controlFalse, Program3.checkInput("-1"));
        assertEquals(controlFalse, Program3.checkInput("ab"));
        assertEquals(controlFalse, Program3.checkInput("1,1"));
        assertEquals(controlTrue, Program3.checkInput("1.1"));
        assertEquals(controlTrue, Program3.checkInput("470"));
    }
    
    @Test
    public void testCheckParameterInput() {
        assertEquals(inputParCases.VALID, Program3.checkParameterInput("123"));
        assertEquals(inputParCases.VALID, Program3.checkParameterInput("234.34"));
        assertEquals(inputParCases.COMMA_INSTEAD_DOT, Program3.checkParameterInput("1,123"));
        assertEquals(inputParCases.PAR_IS_NEGATIVE, Program3.checkParameterInput("-435453.32"));
        assertEquals(inputParCases.PAR_IS_NEGATIVE, Program3.checkParameterInput("-1234,312"));
        assertEquals(inputParCases.TOO_MANY_DIGITS, Program3.checkParameterInput("22222222222222222222221.3333333333333333333331"));
        assertEquals(inputParCases.PAR_IS_NaN, Program3.checkParameterInput("4a7b0"));
    }
}