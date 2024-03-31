TESTS = ["add", "subtract", "multiply", "division"]

for test in TESTS:
    print(f"Running test: {test}")
    exec(f"import test_{test}")
