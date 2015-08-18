function fibonacci(n) {
    if (n == undefined)
        throw "Try calling the main function...";
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}

