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
    testSortStrArray();
    testReverseString();
    testIntToString();
    testStringSearch();
}



/******************************************************************************
    This function displays the details of the test case and its result.

    @param test contains the details to be displayed.
******************************************************************************/
void
displayTestResult(testType test)
{
    styleText(BOLD, true);
    printf("Test case #%d\n", test.testNum);
    styleText(BOLD, false);
    printf("Description: %s\n", test.description);
    printf("Input: %s\n", test.input);
    printf("Expected: %s\n", test.expected);
    printf("Actual: %s\n", test.actual);
    printf("Result: ");
    if (test.result == true)
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
    testType test;
    test.testNum = 0;

    styleText(BOLD, true);
    printf("\nTesting \"isInRange\" function\n\n");
    styleText(BOLD, false);


    //Test case 1
    test.testNum++;
    strcpy(test.description, "The value is outside the given range.");
    strcpy(test.input, "The value is outside the given range.");
    strcpy(test.expected, "false");

    if (isInRange(1, 2, 3))
        strcpy(test.actual, "true");
    else
        strcpy(test.actual, "false");

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);
    

    //Test case 2
    test.testNum++;
    strcpy(test.description, "The value is within range.");
    strcpy(test.input, "Value: 2 ; Min: 1 ; Max: 3");
    strcpy(test.expected, "true");

    if (isInRange(2, 1, 3))
        strcpy(test.actual, "true");
    else
        strcpy(test.actual, "false");

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 3
    test.testNum++;
    strcpy(test.description, "The value, min, and max are equal.");
    strcpy(test.input, "Value: 1 ; Min: 1 ; Max: 1");
    strcpy(test.expected, "true");

    if (isInRange(1, 1, 1))
        strcpy(test.actual, "true");
    else
        strcpy(test.actual, "false");

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);
    

    //Test case 4
    test.testNum++;
    strcpy(test.description, "The value is greater than INT_MAX.");
    strcpy(test.input, "Value: INT_MAX + 1 ; Min: INT_MIN ; Max: INT_MAX");
    strcpy(test.expected, "false");

    if(isInRange((long long) INT_MAX + 1, INT_MIN, INT_MAX))
        strcpy(test.actual, "true");
    else
        strcpy(test.actual, "false");

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);
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
    testType test;
    test.testNum = 0;

    styleText(BOLD, true);
    printf("\nTesting \"FloatInRange\" function\n\n");
    styleText(BOLD, false);


    //Test case 1
    test.testNum++;
    strcpy(test.description, "The value is outside the given range.");
    strcpy(test.input, "Value: 1.0 ; Min: 2.0 ; Max: 3.0");
    strcpy(test.expected, "false");

    if (floatInRange(1.0, 2.0, 3.0))
        strcpy(test.actual, "true");
    else
        strcpy(test.actual, "false");

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);
    

    //Test case 2
    test.testNum++;
    strcpy(test.description, "The value is within range.");
    strcpy(test.input, "Value: 2.0 ; Min: 1.0 ; Max: 3.0");
    strcpy(test.expected, "true");

    if (isInRange(2.0, 1.0, 3.0))
        strcpy(test.actual, "true");
    else
        strcpy(test.actual, "false");

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 3
    test.testNum++;
    strcpy(test.description, "The value, min, and max are equal.");
    strcpy(test.input, "Value: 1.0 ; Min: 1.0 ; Max: 1.0");
    strcpy(test.expected, "true");

    if (floatInRange(1.0, 1.0, 1.0))
        strcpy(test.actual, "true");
    else
        strcpy(test.actual, "false");

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);
    

    //Test case 4
    test.testNum++;
    strcpy(test.description, "The value is greater than FLT_MAX.");
    strcpy(test.input, "Value: FLT_MAX * 2.0 ; Min: FLT_MIN ; Max: FLT_MAX");
    strcpy(test.expected, "false");

    if(floatInRange((double) FLT_MAX * 2.0, FLT_MIN, FLT_MAX))
        strcpy(test.actual, "true");
    else
        strcpy(test.actual, "false");

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);
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
    testType test;
    test.testNum = 0;


    styleText(BOLD, true);
    printf("\nTesting \"stringToInt\" function\n\n");
    styleText(BOLD, false);


    //Test case 1
    test.testNum++;
    strcpy(test.description, "The string is empty.");
    strcpy(test.input, "\"\"");
    strcpy(test.expected, "0");

    snprintf(test.actual, 70, "%d", stringToInt("")); //print the number straight to the array

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 2
    test.testNum++;
    strcpy(test.description, "The string contains a positive number.");
    strcpy(test.input, "\"1\"");
    strcpy(test.expected, "1");

    snprintf(test.actual, 70, "%d", stringToInt("1"));

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);
    

    //Test case 3
    test.testNum++;
    strcpy(test.description, "The string contains a negative number.");
    strcpy(test.input, "\"-1\"");
    strcpy(test.expected, "-1");

    snprintf(test.actual, 70, "%d", stringToInt("-1"));

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);
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
    testType test;
    test.testNum = 0;


    styleText(BOLD, true);
    printf("\nTesting \"stringToFloat\" function\n\n");
    styleText(BOLD, false);


    //Test case 1
    test.testNum++;
    strcpy(test.description, "The string is empty.");
    strcpy(test.input, "\"\"");
    strcpy(test.expected, "0.00");

    snprintf(test.actual, 70, "%.2f", stringToFloat("")); //print the number straight to the array

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 2
    test.testNum++;
    strcpy(test.description, "The string contains a positive number.");
    strcpy(test.input, "\"1.2\"");
    strcpy(test.expected, "1.20");

    snprintf(test.actual, 70, "%.2f", stringToFloat("1.2"));

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);
    

    //Test case 3
    test.testNum++;
    strcpy(test.description, "The string contains a negative number.");
    strcpy(test.input, "\"-1.2\"");
    strcpy(test.expected, "-1.20");

    snprintf(test.actual, 70, "%.2f", stringToFloat("-1.2"));

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 4
    test.testNum++;
    strcpy(test.description, "The string only contains the dot '.' character.");
    strcpy(test.input, "\".\"");
    strcpy(test.expected, "0.00");

    snprintf(test.actual, 70, "%.2f", stringToFloat("."));

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 5
    test.testNum++;
    strcpy(test.description, "The string has multiple instances of the character dot '.'.");
    strcpy(test.input, "\"1.2.3\"");
    strcpy(test.expected, "1.20");

    snprintf(test.actual, 70, "%.2f", stringToFloat("1.2.3"));

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);
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
    testType test;
    test.testNum = 0;


    styleText(BOLD, true);
    printf("\nTesting \"isFileNameValid\" function\n\n");
    styleText(BOLD, false);


    //Test case 1
    test.testNum++;
    strcpy(test.description, "The string is empty.");
    strcpy(test.input, "file = \"\" ; ext = \".txt\"");
    strcpy(test.expected, "false");

    if (isFileNameValid("", ".txt"))
        strcpy(test.actual, "true");
    else
        strcpy(test.actual, "false");

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);

    
    //Test case 2
    test.testNum++;
    strcpy(test.description, "The string only contains the extention.");
    strcpy(test.input, "file = \".txt\" ; ext = \".txt\"");
    strcpy(test.expected, "false");

    if (isFileNameValid(".txt", ".txt"))
        strcpy(test.actual, "true");
    else
        strcpy(test.actual, "false");

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 3
    test.testNum++;
    strcpy(test.description, "The string contains a valid file name.");
    strcpy(test.input, "file = \"test.tXt\" ; ext = \".txt\"");
    strcpy(test.expected, "true");

    if (isFileNameValid("text.tXt", ".txt"))
        strcpy(test.actual, "true");
    else
        strcpy(test.actual, "false");

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 4
    test.testNum++;
    strcpy(test.description, "The string contains disallowed characters.");
    strcpy(test.input, "file = \"he|lo.txt\" ; ext = \".txt\"");
    strcpy(test.expected, "false");

    if (isFileNameValid("he|lo.txt", ".txt"))
        strcpy(test.actual, "true");
    else
        strcpy(test.actual, "false");

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 5
    test.testNum++;
    strcpy(test.description, "The string has an invalid file extention.");
    strcpy(test.input, "file = \"hello.Ttx\" ; ext = \".txt\"");
    strcpy(test.expected, "false");

    if (isFileNameValid("hello.Ttx", ".txt"))
        strcpy(test.actual, "true");
    else
        strcpy(test.actual, "false");

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);
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
    testType test;
    test.testNum = 0;
    string70 string;


    styleText(BOLD, true);
    printf("\nTesting \"convertString\" function\n\n");
    styleText(BOLD, false);


    //Test case 1
    test.testNum++;
    strcpy(test.description, "The string is empty.");
    strcpy(test.input, "str = \"\" ; type = UPPER_CASE");
    strcpy(test.expected, "");

    strcpy(string, "");
    strcpy(test.actual, convertString(string, UPPER_CASE));

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 2
    test.testNum++;
    strcpy(test.description, "Only lower case letters converted into upper case.");
    strcpy(test.input, "str = \"abcde\" ; type = UPPER_CASE");
    strcpy(test.expected, "ABCDE");

    strcpy(string, "abcde");
    strcpy(test.actual, convertString(string, UPPER_CASE));

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 3
    test.testNum++;
    strcpy(test.description, "Only upper case letters converted into upper case.");
    strcpy(test.input, "str = \"ABCDE\" ; type = UPPER_CASE");
    strcpy(test.expected, "ABCDE");

    strcpy(string, "ABCDE");
    strcpy(test.actual, convertString(string, UPPER_CASE));

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 4
    test.testNum++;
    strcpy(test.description, "Mix of both upper and lower case letters converted into upper case.");
    strcpy(test.input, "str = \"aBcDE\" ; type = UPPER_CASE");
    strcpy(test.expected, "ABCDE");

    strcpy(string, "aBcDE");
    strcpy(test.actual, convertString(string, UPPER_CASE));

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 5
    test.testNum++;
    strcpy(test.description, "Only lower case letters converted into lower case.");
    strcpy(test.input, "str = \"abcde\" ; type = LOWER_CASE");
    strcpy(test.expected, "abcde");
    strcpy(string, "abcde");
    strcpy(test.actual, convertString(string, LOWER_CASE));

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 6
    test.testNum++;
    strcpy(test.description, "Only upper case letters converted into lower case.");
    strcpy(test.input, "str = \"ABCDE\" ; type = LOWER_CASE");
    strcpy(test.expected, "abcde");
    strcpy(string, "ABCDE");
    strcpy(test.actual, convertString(string, LOWER_CASE));

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);

    
    //Test case 7
    test.testNum++;
    strcpy(test.description, "Mix of both upper and lower case letters converted into lower case.");
    strcpy(test.input, "str = \"aBcDE\" ; type = LOWER_CASE");
    strcpy(test.expected, "abcde");
    strcpy(string, "aBcDE");
    strcpy(test.actual, convertString(string, LOWER_CASE));

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);
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
    testType test;
    test.testNum = 0;
    int result;


    styleText(BOLD, true);
    printf("\nTesting \"absStrCmp\" function\n\n");
    styleText(BOLD, false);


    //Test case 1
    test.testNum++;
    strcpy(test.description, "The string is empty.");
    strcpy(test.input, "str1 = \"\" ; str2 = \"\"");
    strcpy(test.expected, "EQUAL");

    result = absStrCmp("", "");

    if (result == 0)
        strcpy(test.actual, "EQUAL");
    else if (result > 0)
        strcpy(test.actual, "POSITIVE");
    else if (result < 0)
        strcpy(test.actual , "NEGATIVE");

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 2
    test.testNum++;
    strcpy(test.description, "The strings are equal to each other.");
    strcpy(test.input, "str1 = \"aBc\" ; str2 = \"ABc\"");
    strcpy(test.expected, "EQUAL");

    result = absStrCmp("aBc", "ABc");

    if (result == 0)
        strcpy(test.actual, "EQUAL");
    else if (result > 0)
        strcpy(test.actual, "POSITIVE");
    else if (result < 0)
        strcpy(test.actual , "NEGATIVE");

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 3
    test.testNum++;
    strcpy(test.description, "Str1 is greater than str2.");
    strcpy(test.input, "str1 = \"Def\" ; str2 = \"aBc\"");
    strcpy(test.expected, "POSITIVE");

    result = absStrCmp("Def", "aBc");

    if (result == 0)
        strcpy(test.actual, "EQUAL");
    else if (result > 0)
        strcpy(test.actual, "POSITIVE");
    else if (result < 0)
        strcpy(test.actual , "NEGATIVE");

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 4
    test.testNum++;
    strcpy(test.description, "Str1 is less than str2.");
    strcpy(test.input, "str1 = \"aBc\" ; str2 = \"Def\"");
    strcpy(test.expected, "NEGATIVE");

    result = absStrCmp("aBc", "Def");

    if (result == 0)
        strcpy(test.actual, "EQUAL");
    else if (result > 0)
        strcpy(test.actual, "POSITIVE");
    else if (result < 0)
        strcpy(test.actual , "NEGATIVE");

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);
}



/******************************************************************************
    This function tests whether the function "sortStrArray" works as expected.
    Test Cases:
        1. The arrays are empty.
        2. Every string are equal to each other. Increasing order.
        3. Contains unique strings in a increasing order. Increasing order.
        4. Contains unique strings in a random order. Increasing order.
        5. Contains unique strings in a decreasing order. Decreasing order.
        6. Contains unique strings in a random order. Decreasing order.
******************************************************************************/
void
testSortStrArray()
{
    testType test;
    test.testNum = 0;
    strcpy(test.actual, "");
    char str[3][20];


    styleText(BOLD, true);
    printf("\nTesting \"sortStrArray\" function\n\n");
    styleText(BOLD, false);


    //Test case 1
    test.testNum++;
    strcpy(test.description, "The arrays are empty.");
    strcpy(test.input, "arr[0] = \"\", arr[1] = \"\", arr[2] = \"\"");
    strcpy(test.expected, ",,");

    strcpy(str[0], "");
    strcpy(str[1], "");
    strcpy(str[2], "");

    sortStrArray(INCREASING, 3, 20, str);

    arrayToString(20, 3, str, test.actual);
    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 2
    test.testNum++;
    strcpy(test.description, "Every string are equal to each other. Increasing order.");
    strcpy(test.input, "arr[0] = \"abc\", arr[1] = \"abc\", arr[2] = \"abc\" ; type = INCREASING");
    strcpy(test.expected, "abc,abc,abc");

    strcpy(str[0], "abc");
    strcpy(str[1], "abc");
    strcpy(str[2], "abc");

    sortStrArray(INCREASING, 3, 20, str);

    arrayToString(20, 3, str, test.actual);
    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 3
    test.testNum++;
    strcpy(test.description, "Contains unique strings in a increasing order. Increasing order.");
    strcpy(test.input, "arr[0] = \"abc\", arr[1] = \"def\", arr[2] = \"ghi\" ; type = INCREASING");
    strcpy(test.expected, "abc,def,ghi");

    strcpy(str[0], "abc");
    strcpy(str[1], "def");
    strcpy(str[2], "ghi");

    sortStrArray(INCREASING, 3, 20, str);

    arrayToString(20, 3, str, test.actual);
    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 4
    test.testNum++;
    strcpy(test.description, "Contains unique strings in a random order. Increasing order.");
    strcpy(test.input, "arr[0] = \"ghi\", arr[1] = \"abc\", arr[2] = \"def\" ; type = INCREASING");
    strcpy(test.expected, "abc,def,ghi");

    strcpy(str[0], "ghi");
    strcpy(str[1], "abc");
    strcpy(str[2], "def");

    sortStrArray(INCREASING, 3, 20, str);

    arrayToString(20, 3, str, test.actual);
    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 5
    test.testNum++;
    strcpy(test.description, "Contains unique strings in a decreasing order. Decreasing order.");
    strcpy(test.input, "arr[0] = \"ghi\", arr[1] = \"def\", arr[2] = \"abc\" ; type = DECREASING");
    strcpy(test.expected, "ghi,def,abc");

    strcpy(str[0], "ghi");
    strcpy(str[1], "def");
    strcpy(str[2], "abc");

    sortStrArray(DECREASING, 3, 20, str);

    arrayToString(20, 3, str, test.actual);
    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 6
    test.testNum++;
    strcpy(test.description, "Contains unique strings in a random order. Decreasing order.");
    strcpy(test.input, "arr[0] = \"ghi\", arr[1] = \"abc\", arr[2] = \"def\" ; type = DECREASING");
    strcpy(test.expected, "ghi,def,abc");

    strcpy(str[0], "ghi");
    strcpy(str[1], "abc");
    strcpy(str[2], "def");

    sortStrArray(DECREASING, 3, 20, str);

    arrayToString(20, 3, str, test.actual);
    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);
}



/******************************************************************************
    This function tests whether the function "reverseString" works as expected.
    Test Cases:
        1. The string is empty.
        2. The string contains characters.
******************************************************************************/
void
testReverseString()
{
    testType test;
    test.testNum = 0;
    string70 temp;


    styleText(BOLD, true);
    printf("\nTesting \"reverseString\" function\n\n");
    styleText(BOLD, false);


    //Test case 1
    test.testNum++;
    strcpy(test.description, "The string is empty.");
    strcpy(test.input, "");
    strcpy(test.expected, "");

    strcpy(temp, "");
    strcpy(test.actual, reverseString(temp));

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 2
    test.testNum++;
    strcpy(test.description, "The string contains characters.");
    strcpy(test.input, "abc");
    strcpy(test.expected, "cba");

    strcpy(temp, "abc");
    strcpy(test.actual, reverseString(temp));

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);
}



/******************************************************************************
    This function tests whether the function "intToString" works as expected.
    Test Cases:
        1. The integer is zero.
        2. The integer is positive.
        3. The integer is negative.
******************************************************************************/
void
testIntToString()
{
    testType test;
    test.testNum = 0;
    strcpy(test.actual, "");


    styleText(BOLD, true);
    printf("\nTesting \"intToString\" function\n\n");
    styleText(BOLD, false);


    //Test case 1
    test.testNum++;
    strcpy(test.description, "The integer is zero.");
    strcpy(test.input, "0");
    strcpy(test.expected, "0");

    intToString(0, test.actual);

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 2
    test.testNum++;
    strcpy(test.description, "The integer is positive.");
    strcpy(test.input, "1234567");
    strcpy(test.expected, "1234567");

    intToString(1234567, test.actual);

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 3
    test.testNum++;
    strcpy(test.description, "The integer is negative.");
    strcpy(test.input, "-1234567");
    strcpy(test.expected, "-1234567");

    intToString(-1234567, test.actual);

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);
}



/******************************************************************************
    This function tests whether the function "stringSearch" works as expected.
    Test Cases:
        1. The array contains the string.
        2. The array does not contain the string.
        3. There are multiple instances of the key.
******************************************************************************/
void
testStringSearch()
{
    testType test;
    test.testNum = 0;
    strcpy(test.actual, "");
    string20 arr[3];
    int result;


    styleText(BOLD, true);
    printf("\nTesting \"stringSearch\" function\n\n");
    styleText(BOLD, false);


    //Test case 1
    test.testNum++;
    strcpy(test.description, "The array contains the string.");
    strcpy(test.input, "arr[0] = \"abc\", arr[1] = \"def\", arr[2] = \"ghi\" ; key = \"def\"");
    strcpy(test.expected, "1");

    strcpy(arr[0], "abc");
    strcpy(arr[1], "def");
    strcpy(arr[2], "ghi");

    result = stringSearch(3, 21, arr, "def");
    intToString(result, test.actual);

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 2
    test.testNum++;
    strcpy(test.description, "The array does not contain the string.");
    strcpy(test.input, "arr[0] = \"abc\", arr[1] = \"def\", arr[2] = \"ghi\" ; key = \"jkf\"");
    strcpy(test.expected, "-1");

    strcpy(arr[0], "abc");
    strcpy(arr[1], "def");
    strcpy(arr[2], "ghi");

    result = stringSearch(3, 21, arr, "jkf");
    intToString(result, test.actual);

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);


    //Test case 3
    test.testNum++;
    strcpy(test.description, "There are multiple instances of the key.");
    strcpy(test.input, "arr[0] = \"abc\", arr[1] = \"abc\", arr[2] = \"abc\" ; key = \"abc\"");
    strcpy(test.expected, "0");

    strcpy(arr[0], "abc");
    strcpy(arr[1], "abc");
    strcpy(arr[2], "abc");

    result = stringSearch(3, 21, arr, "abc");
    intToString(result, test.actual);

    test.result = (strcmp(test.expected, test.actual) == 0);

    displayTestResult(test);
}



#endif