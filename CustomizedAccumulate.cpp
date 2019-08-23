#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// function returns addition of 2 values
int add(int left, int right)
{
    return left + right;
}

// function returns subtraction of 2 values
int sub(int left, int right)
{
    return left - right;
}

// function returns bitwiseAnd value of 2 values
int bitAnd(int left, int right)
{
    return left & right;
}

// function returns bitwiseOr value of 2 values
int bitOr(int left, int right)
{
    return left | right;
}

// function returns bitwiseXor value of 2 values
int bitXor(int left, int right)
{
    return left ^ right;
}

// function returns pre concatanation string of 2 strings
string preConcat(string left, string right)
{
    return left + right;
}

// function returns post concatanation string of 2 strings
string postConcat(string left, string right)
{
    return right + left;
}

// Declaring 2 global maps for integer and string operations
map<string, int(*)(int, int)> integer_operators;
map<string, string(*)(string, string)> string_operators;

// Populating the function addresses to the respective map indexes
void populate_binary_operator_function_objects_map()
{
    integer_operators["add"] = &add;
    integer_operators["sub"] = &sub;
    integer_operators["bitwise_and"] = &bitAnd;
    integer_operators["bitwise_or"] = &bitOr;
    integer_operators["bitwise_xor"] = &bitXor;
	
    string_operators["pre_concat"] = &preConcat;
    string_operators["post_concat"] = &postConcat;
}

/*
Definition of the customized_accumulate generic function to work on both
integer as well as string operations.
*/
template <typename InputIterator, typename GenericType>
GenericType customized_accumulate(InputIterator firstPosition, InputIterator lastPosition,
GenericType (*firstFunction)(GenericType, GenericType), GenericType (*secondFunction)(GenericType, GenericType))
{
    GenericType result;
    // If the array contains only 1 value then returns only that value
    if(firstPosition == lastPosition-1)
    {
        return *firstPosition;
    }
    // Iterating the whole array to perform operations
    for(int i = 1; firstPosition < lastPosition-1; firstPosition++, i++)
    {
        if(i == 1)
        {
            // First operation with first and second values of the array
            result = firstFunction(*firstPosition, *(firstPosition+1));
        }
        else
        {
            if(i%2 == 0)
            {
                // Second operation with result value and next value of the array
                result = secondFunction(result, *(firstPosition+1));
            }
            else
            {
                // First operation with result value and next value of the array
                result = firstFunction(result, *(firstPosition+1));
            }
        }
    }
    // Returns the result
    return result;
}

void validate_binary_operator_function_objects()
{
    assert(integer_operators["add"](3, 5) == 8);
    assert(integer_operators["sub"](3, 5) == -2);
    assert(integer_operators["bitwise_and"](3, 5) == 1);
    assert(integer_operators["bitwise_or"](3, 5) == 7);
    assert(integer_operators["bitwise_xor"](3, 5) == 6);

    assert(string_operators["pre_concat"]("abc", "pqrs") == "abcpqrs");
    assert(string_operators["post_concat"]("abc", "pqrs") == "pqrsabc");
}

void validate_customized_accumulate()
{
    std::string type;
    int n;
    std::cin >> type >> n;

    std::vector<std::string> str_arr(n);
    for (int i = 0; i < n; i++)
	{
        std::cin >> str_arr[i];
    }

    std::string first_key, second_key;
    std::cin >> first_key >> second_key;

    if (type == "String")
	{
        auto first_operator = string_operators[first_key];
        auto second_operator = string_operators[second_key];

        std::cout << customized_accumulate(begin(str_arr), end(str_arr), first_operator, second_operator) << std::endl;
    }
	else
	{
        std::vector<int> int_arr(n);
        for (int i = 0; i < n; i++)
		{
            int_arr[i] = stoi(str_arr[i]);
        }

        auto first_operator = integer_operators[first_key];
        auto second_operator = integer_operators[second_key];

        std::cout << customized_accumulate(begin(int_arr), end(int_arr), first_operator, second_operator) << std::endl;
    }
}

int main()
{
    populate_binary_operator_function_objects_map();
    validate_binary_operator_function_objects();

    int q;
    std::cin >> q;

    while (q--)
	{
        validate_customized_accumulate();
    }

    return 0;
}
