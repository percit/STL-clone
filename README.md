# C++ Template
This is a C++ project template that you can use as a starting point for setting up your new project in GitLab, or use it as a reference if you would like to setup a CI Pipeline in your existing GitLab project.

## Requirements
- **Compiler:** g++-12
- **Build tool:** [cmake](https://cmake.org/)
- **Tests:** [GoogleTest](https://google.github.io/googletest/) (gtest, gmock), [CTest](https://cmake.org/cmake/help/latest/manual/ctest.1.html)
- **Static Analysis:** Clang-tidy, Clang-format

## Build project (with Docker)

To build this project inside a docker container, you have to have a docker image, which can be downloaded from Gitlab Docker Registry from [Cpp Builder project](https://gitlab.siilicloud.com/automotive/containers/cpp-builder).

Please follow those commands to build the project:

1. Clone repository:
```bash
git clone git@gitlab.siilicloud.com:automotive/project-templates/cpp-template.git
```
2. Change directory into the project:
```bash
cd cpp-template
```
3. Run docker container (it will pull also the image from registry):
```bash
./tools/run-docker.sh
```
4. Once you will be inside the container you can build the project, by running `build.sh` script:
```bash
./tools/build.sh
```
or by running following commands:
```bash
cmake -S . -B build/ -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-std=c++17" -DCMAKE_CXX_COMPILER=g++-12 -DBUILD_TESTS=ON
cmake --build build/
```

## Static analysis

In Code Quality you can see raports what is wrong, if you would like to run them locally use scripts from 'tools' directory.

To run static analysis you can change .clang-tidy and .clang-format and run scripts clang-tidy.sh and clang-format.sh. For scripts to work, you have to run "chmod +x" before adding to repository, running those in .yaml script won't work.

## Tests

Runs the unit tests for C++ code using the Google Test framework and generates a JUnit XML report.

### CI Configuration

To configure the test stage in CI pipeline, and enable or disable it, you can modify `RUN_TESTS` variable in `.gitlab-ci.yml` file.

For example:
```yml
variables:
  ...
  RUN_TESTS: "OFF" # turn off Test job in CI pipeline
```

### CI Test Report

Tests stage generates an XML report that can be used to view the results of the unit tests. The reports are saved in `build/tests/reports/` directory **by default**, and all files that are in this directory and follow "`test_report-*.xml`" naming pattern are saved as an artifact and are available for download in the GitLab pipeline job.

You can also view the test report in the GitLab UI by navigating to the pipeline job and clicking on the `Tests` tab.

### Modify tests report path in CI
To specify custom test report path you have to change the value of `reports_path` **spec:input** (which is `build/tests/reports/` by default) in `.gitlab-ci.yml` file in the section where tests template is included:
```yml
# Include job definition templates
include:
  ...
  - project: 'automotive/ci-templates'
    ref: 'main'
    file: 'tests-cpp.gitlab-ci.yml'
    with:
      reports_path: "custom/reports/path/test_report-*.xml"
```
Artifacts of tests reports (all XML files starting with `test_report-`) will be gathered from that path.
Please note that this value needs to align with the path that is in your `CMakeLists.txt` where the actual test executable is saving the test report to.

For example:

```bash
add_test(
  NAME Test1
  COMMAND test1 --gtest_output=xml:custom/reports/path/test_report-test1.xml
)
```

### Build tests locally

In order to build tests locally you have to set `DBUILD_TESTS` flag to your **cmake** command and turn them **ON** or **OFF**:

```bash
-DBUILD_TESTS=ON
```

So the complete cmake command for generating and building the project will look like this:
```bash
cmake -S . -B build/ -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-std=c++17" -DCMAKE_CXX_COMPILER=g++ -DBUILD_TESTS=ON

cmake --build build/
```

### Running tests locally

To manualy run specific test locally and generate the `GTest` XML test report you can use following command:
``` bash
./build/tests/test1 --gtest_output="xml:build/tests/reports/test_report.xml"
```

Or you can run all tests specified in `CMakeLists.txt` in your build directory by running `ctest` tool:
``` bash
ctest ctest --test-dir build/ --output-on-failure
```

To generate `ctest` JUnit XML test report use following command:
``` bash
ctest ctest --test-dir build/ --output-on-failure --output-junit reports/test_report.xml
```

### Troubleshooting
If the tests stage fails, check the GitLab pipeline logs and the `test_report-*.xml` file for error messages and failed tests.

Make sure that your C++ code and test cases are written correctly and that the CMake command and custom test runner are configured properly.

## Adding aditional jobs

If you want to add new job, you have to add name to "stages" and add new job, if you want to delete one, you have to delete the job itself, and the name from stages.

