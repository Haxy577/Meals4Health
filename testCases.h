#ifndef TESTCASES_H
#define TESTCASES_H
#include "prototypes.h"


/******************************************************************************
*                                                                             *
*                             Testing Functions                               *
*                                                                             *
******************************************************************************/


/******************************************************************************
    This function calls all the test functions.
******************************************************************************/
void
testAllFunctions()
{
    testIsInRange();
    testFloatInRange();
    testStringToInt();
    testStringToFloat();
    testIsFileNameValid();
    testConvertString();
    testAbsStrCmp();
}



/******************************************************************************
    This function displays the details of the test case and its result.

    @param testNum the test case number.
    @param description the description of the test case.
    @param input what was inputted in the function parameters.
    @param expected the expected output of the function.
    @param actual the actual output of the function.
    @param result whether the expected matches the actual. Prints "PASS" if
        it matches, "FAIL" if it does not.
******************************************************************************/
void
displayTestResult(int testNum,
              string70 description,
              string70 input,
              string70 expected,
              string70 actual,
              bool result)
{
    styleText(BOLD, TRUE);
    printf("Test case #%d\n", testNum);
    styleText(BOLD, FALSE);
    printf("Description: %s\n", description);
    printf("Input: %s\n", input);
    printf("Expected: %s\n", expected);
    printf("Actual: %s\n", actual);
    printf("Result: ");
    if (result == TRUE)
    {
        paintText(FOREGROUND, 0 ,255, 0);
        printf("PASS\n\n");
    }
    else
    {
        paintText(FOREGROUND, 255, 0, 0);
        printf("FAIL\n\n");
    }
    resetText();
}



/******************************************************************************
    This function tests whether the function "isInRange" works as expected.
    Test Cases:
        1. The value is within the given range.
        2. The value is outside the given range.
        3. The value, min, and max are equal.
        4. The value is greater than INT_MAX.
******************************************************************************/
void
testIsInRange()
{
    int testNum = 0;
    string70 expected;
    string70 actual;

    styleText(BOLD, TRUE);
    printf("\nTesting \"isInRange\" function\n\n");
    styleText(BOLD, FALSE);

    //Test case 1
    strcpy(expected, "FALSE");

    if (isInRange(1, 2, 3))
        strcpy(actual, "TRUE");
    else
        strcpy(actual, "FALSE");

    displayTestResult(++testNum,
                      "The value is outside the given range.",
                      "Value: 1 ; Min: 2 ; Max: 3",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);
    
    //Test case 2
    strcpy(expected, "TRUE");

    if (isInRange(2, 1, 3))
        strcpy(actual, "TRUE");
    else
        strcpy(actual, "FALSE");

    displayTestResult(++testNum,
                      "The value is within range.",
                      "Value: 2 ; Min: 1 ; Max: 3",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);

    //Test case 3
    strcpy(expected, "TRUE");

    if (isInRange(1, 1, 1))
        strcpy(actual, "TRUE");
    else
        strcpy(actual, "FALSE");

    displayTestResult(++testNum,
                      "The value, min, and max are equal.",
                      "Value: 1 ; Min: 1 ; Max: 1",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);
    
    //Test case 4
    strcpy(expected, "FALSE");

    if(isInRange((long long) INT_MAX + 1, INT_MIN, INT_MAX))
        strcpy(actual, "TRUE");
    else
        strcpy(actual, "FALSE");

        displayTestResult(++testNum,
                          "The value is greater than INT_MAX.",
                          "Value: INT_MAX + 1 ; Min: INT_MIN ; Max: INT_MAX",
                          expected,
                          actual,
                          strcmp(expected, actual) == 0);
}



/******************************************************************************
    This function tests whether the function "floatInRange" works as expected.
    Test Cases:
        1. The value is within the given range.
        2. The value is outside the given range.
        3. The value, min, and max are equal.
        4. The value is greater than FLT_MAX.
******************************************************************************/
void
testFloatInRange()
{
    int testNum = 0;
    string70 expected;
    string70 actual;

    styleText(BOLD, TRUE);
    printf("\nTesting \"FloatInRange\" function\n\n");
    styleText(BOLD, FALSE);

    //Test case 1
    strcpy(expected, "FALSE");

    if (floatInRange(1.0, 2.0, 3.0))
        strcpy(actual, "TRUE");
    else
        strcpy(actual, "FALSE");

    displayTestResult(++testNum,
                      "The value is outside the given range.",
                      "Value: 1.0 ; Min: 2.0 ; Max: 3.0",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);
    
    //Test case 2
    strcpy(expected, "TRUE");

    if (isInRange(2.0, 1.0, 3.0))
        strcpy(actual, "TRUE");
    else
        strcpy(actual, "FALSE");

    displayTestResult(++testNum,
                      "The value is within range.",
                      "Value: 2.0 ; Min: 1.0 ; Max: 3.0",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);

    //Test case 3
    strcpy(expected, "TRUE");

    if (floatInRange(1.0, 1.0, 1.0))
        strcpy(actual, "TRUE");
    else
        strcpy(actual, "FALSE");

    displayTestResult(++testNum,
                      "The value, min, and max are equal.",
                      "Value: 1.0 ; Min: 1.0 ; Max: 1.0",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);
    
    //Test case 4
    strcpy(expected, "FALSE");

    if(floatInRange((double) FLT_MAX * 2.0, FLT_MIN, FLT_MAX))
        strcpy(actual, "TRUE");
    else
        strcpy(actual, "FALSE");

        displayTestResult(++testNum,
                          "The value is greater than INT_MAX.",
                          "Value: FLT_MAX * 2.0 ; Min: FLT_MIN ; Max: FLT_MAX",
                          expected,
                          actual,
                          strcmp(expected, actual) == 0);
}



/******************************************************************************
    This function tests whether the function "stringToInt" works as expected.
    Test Cases:
        1. The string is empty.
        2. The string contains a positive number.
        3. The string contains a negative number.
******************************************************************************/
void
testStringToInt()
{
    int testNum = 0;
    string70 expected;
    string70 actual;

    styleText(BOLD, TRUE);
    printf("\nTesting \"stringToInt\" function\n\n");
    styleText(BOLD, FALSE);

    //Test case 1
    strcpy(expected, "0");

    snprintf(actual, 70, "%d", stringToInt("")); //print the number straight to the array

    displayTestResult(++testNum,
                      "The string is empty.",
                      "\"\"",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);

    //Test case 2
    strcpy(expected, "1");

    snprintf(actual, 70, "%d", stringToInt("1"));

    displayTestResult(++testNum,
                      "The string contains a positive number.",
                      "\"1\"",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);
    
    //Test case 3
    strcpy(expected, "-1");

    snprintf(actual, 70, "%d", stringToInt("-1"));

    displayTestResult(++testNum,
                      "The string contains a negative number.",
                      "\"-1\"",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);
}



/******************************************************************************
    This function tests whether the function "stringToFloat" works as expected.
    Test Cases:
        1. The string is empty.
        2. The string contains a positive number.
        3. The string contains a negative number.
        4. The string only contains the dot '.' character.
        5. The string has multiple instances of the character dot '.'.
******************************************************************************/
void
testStringToFloat()
{
    int testNum = 0;
    string70 expected;
    string70 actual;

    styleText(BOLD, TRUE);
    printf("\nTesting \"stringToFloat\" function\n\n");
    styleText(BOLD, FALSE);

    //Test case 1
    strcpy(expected, "0.00");

    snprintf(actual, 70, "%.2f", stringToFloat("")); //print the number straight to the array

    displayTestResult(++testNum,
                      "The string is empty.",
                      "\"\"",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);

    //Test case 2
    strcpy(expected, "1.20");

    snprintf(actual, 70, "%.2f", stringToFloat("1.2"));

    displayTestResult(++testNum,
                      "The string contains a positive number.",
                      "\"1.2\"",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);
    
    //Test case 3
    strcpy(expected, "-1.20");

    snprintf(actual, 70, "%.2f", stringToFloat("-1.2"));

    displayTestResult(++testNum,
                      "The string contains a negative number.",
                      "\"-1.2\"",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);

    //Test case 4
    strcpy(expected, "0.00");

    snprintf(actual, 70, "%.2f", stringToFloat("."));

    displayTestResult(++testNum,
                      "The string only contains the dot '.' character.",
                      "\".\"",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);

    //Test case 5
    strcpy(expected, "1.20");

    snprintf(actual, 70, "%.2f", stringToFloat("1.2.3"));

    displayTestResult(++testNum,
                      "The string has multiple instances of the character dot '.'.",
                      "\"1.2.3\"",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);
}



/******************************************************************************
    This function tests whether the function "isFileNameValid" works as expected.
    Test Cases:
        1. The string is empty.
        2. The string only contains the extention.
        3. The string contains a valid file name.
        4. The string contains disallowed characters.
        5. The string has an invalid file extention.
******************************************************************************/
void
testIsFileNameValid()
{
    int testNum = 0;
    string70 expected;
    string70 actual;

    styleText(BOLD, TRUE);
    printf("\nTesting \"isFileNameValid\" function\n\n");
    styleText(BOLD, FALSE);

    //Test case 1
    strcpy(expected, "FALSE");

    if (isFileNameValid("", ".txt"))
        strcpy(actual, "TRUE");
    else
        strcpy(actual, "FALSE");

    displayTestResult(++testNum,
                      "The string is empty.",
                      "file = \"\" ; ext = \".txt\"",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);

    //Test case 2
    strcpy(expected, "FALSE");

    if (isFileNameValid(".txt", ".txt"))
        strcpy(actual, "TRUE");
    else
        strcpy(actual, "FALSE");

    displayTestResult(++testNum,
                      "The string only contains the extention.",
                      "file = \".txt\" ; ext = \".txt\"",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);

    //Test case 3
    strcpy(expected, "TRUE");

    if (isFileNameValid("text.tXt", ".txt"))
        strcpy(actual, "TRUE");
    else
        strcpy(actual, "FALSE");

    displayTestResult(++testNum,
                      "The string contains a valid file name.",
                      "file = \"test.tXt\" ; ext = \".txt\"",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);

    //Test case 4
    strcpy(expected, "FALSE");

    if (isFileNameValid("he|lo.txt", ".txt"))
        strcpy(actual, "TRUE");
    else
        strcpy(actual, "FALSE");

    displayTestResult(++testNum,
                      "The string contains disallowed characters.",
                      "file = \"he|lo.txt\" ; ext = \".txt\"",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);

    //Test case 5
    strcpy(expected, "FALSE");

    if (isFileNameValid("hello.Ttx", ".txt"))
        strcpy(actual, "TRUE");
    else
        strcpy(actual, "FALSE");

    displayTestResult(++testNum,
                      "The string has an invalid file extention.",
                      "file = \"hello.Ttx\" ; ext = \".txt\"",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);
}



/******************************************************************************
    This function tests whether the function "convertString" works as expected.
    Test Cases:
        1. The string is empty.
        2. Only lower case letters converted into upper case.
        3. Only upper case letters converted into upper case.
        4. Mix of both upper and lower case letters converted into upper case.
        5. Only lower case letters converted into lower case.
        6. Only upper case letters converted into lower case.
        7. Mix of both upper and lower case letters converted into lower case.
******************************************************************************/
void
testConvertString()
{
    int testNum = 0;
    string70 input;
    string70 expected;
    string70 actual;

    styleText(BOLD, TRUE);
    printf("\nTesting \"convertString\" function\n\n");
    styleText(BOLD, FALSE);

    //Test case 1
    strcpy(expected, "");
    strcpy(input, "");
    strcpy(actual, convertString(input, UPPER_CASE));

    displayTestResult(++testNum,
                      "The string is empty.",
                      "str = \"\" ; type = UPPER_CASE",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);

    //Test case 2
    strcpy(expected, "ABCDE");
    strcpy(input, "abcde");
    strcpy(actual, convertString(input, UPPER_CASE));

    displayTestResult(++testNum,
                      "Only lower case letters converted into upper case.",
                      "str = \"abcde\" ; type = UPPER_CASE",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);

    //Test case 3
    strcpy(expected, "ABCDE");
    strcpy(input, "ABCDE");
    strcpy(actual, convertString(input, UPPER_CASE));

    displayTestResult(++testNum,
                      "Only upper case letters converted into upper case.",
                      "str = \"ABCDE\" ; type = UPPER_CASE",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);

    //Test case 4
    strcpy(expected, "ABCDE");
    strcpy(input, "aBcDE");
    strcpy(actual, convertString(input, UPPER_CASE));

    displayTestResult(++testNum,
                      "Mix of both upper and lower case letters converted into upper case.",
                      "str = \"aBcDE\" ; type = UPPER_CASE",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);

    //Test case 5
    strcpy(expected, "abcde");
    strcpy(input, "abcde");
    strcpy(actual, convertString(input, LOWER_CASE));

    displayTestResult(++testNum,
                      "Only lower case letters converted into lower case.",
                      "str = \"abcde\" ; type = LOWER_CASE",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);

    //Test case 6
    strcpy(expected, "abcde");
    strcpy(input, "ABCDE");
    strcpy(actual, convertString(input, LOWER_CASE));

    displayTestResult(++testNum,
                      "Only upper case letters converted into lower case.",
                      "str = \"ABCDE\" ; type = LOWER_CASE",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);

    //Test case 7
    strcpy(expected, "abcde");
    strcpy(input, "aBcDE");
    strcpy(actual, convertString(input, LOWER_CASE));

    displayTestResult(++testNum,
                      "Mix of both upper and lower case letters converted into lower case.",
                      "str = \"aBcDE\" ; type = LOWER_CASE",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);
}



/******************************************************************************
    This function tests whether the function "absStrCmp" works as expected.
    Test Cases:
        1. The strings are empty.
        2. The strings are equal to each other.
        3. Str1 is greater than str2.
        4. Str1 is less than str2.
******************************************************************************/
void
testAbsStrCmp()
{
    int testNum = 0;
    int result;
    string70 expected;
    string70 actual;

    styleText(BOLD, TRUE);
    printf("\nTesting \"absStrCmp\" function\n\n");
    styleText(BOLD, FALSE);

    //Test case 1
    strcpy(expected, "EQUAL");
    result = absStrCmp("", "");

    if (result == 0)
        strcpy(actual, "EQUAL");
    else if (result > 0)
        strcpy(actual, "POSITIVE");
    else if (result < 0)
        strcpy(actual , "NEGATIVE");

    displayTestResult(++testNum,
                      "The string is empty.",
                      "str1 = \"\" ; str2 = \"\"",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);

    //Test case 2
    strcpy(expected, "EQUAL");
    result = absStrCmp("aBc", "ABc");

    if (result == 0)
        strcpy(actual, "EQUAL");
    else if (result > 0)
        strcpy(actual, "POSITIVE");
    else if (result < 0)
        strcpy(actual , "NEGATIVE");

    displayTestResult(++testNum,
                      "The strings are equal to each other.",
                      "str1 = \"aBc\" ; str2 = \"ABc\"",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);

    //Test case 3
    strcpy(expected, "POSITIVE");
    result = absStrCmp("Def", "aBc");

    if (result == 0)
        strcpy(actual, "EQUAL");
    else if (result > 0)
        strcpy(actual, "POSITIVE");
    else if (result < 0)
        strcpy(actual , "NEGATIVE");

    displayTestResult(++testNum,
                      "Str1 is greater than str2.",
                      "str1 = \"Def\" ; str2 = \"aBc\"",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);

    //Test case 4
    strcpy(expected, "NEGATIVE");
    result = absStrCmp("aBc", "Def");

    if (result == 0)
        strcpy(actual, "EQUAL");
    else if (result > 0)
        strcpy(actual, "POSITIVE");
    else if (result < 0)
        strcpy(actual , "NEGATIVE");

    displayTestResult(++testNum,
                      "Str1 is less than str2.",
                      "str1 = \"aBc\" ; str2 = \"Def\"",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);
}



#endif