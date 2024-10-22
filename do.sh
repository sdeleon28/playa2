function print_usage() {
  echo ""
  echo "SYNOPSIS"
  echo ""
  echo "  ./do.sh [
      |config
      |build
      |run
      |br: build and run
      |make: config, build and run
      |lsp
      |help
  ]"
}

function configure() {
  mkdir -p build
  cmake \
    -DCMAKE_BUILD_TYPE:STRING=Debug \
    -H"." \
    -B"build/tui" \
    -G Ninja
}

function build() {
  cmake --build build/tui --target Playa2Tui
}

function run() {
  ./build/tui/Projects/Playa2/Playa2Tui_artefacts/Debug/Playa2Tui "$@"
}

function configure_lsp() {
  mkdir -p build
  rm -rf build/tui-lsp
  cmake \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DCMAKE_BUILD_TYPE:STRING=Debug \
    -H"." \
    -B"build/tui-lsp" \
    -G Ninja
  rm -f compile_commands.json
  ln -s build/tui-lsp/compile_commands.json compile_commands.json
  cmake --build build/tui-lsp --target Playa2Tui
}

function configure_test() {
  mkdir -p build
  cmake \
    -DJUCE_BUILD_EXTRAS=ON \
    -DCMAKE_BUILD_TYPE:STRING=Debug \
    -H"." \
    -B"build/test" \
    -G Ninja
}

function run_test() {
  if [ -d "build/test" ]; then
    echo "+++ The build/test directory exists. Skipping config step."
  else
    configure_test
  fi
  cmake --build build/test --target Playa2Tests
  ./build/test/Projects/Playa2Tests/Playa2Tests_artefacts/Debug/Playa2Tests
}

case $1 in
  config)
    configure
    ;;
  build)
    build
    ;;
  run)
    run "${@:2}"
    ;;
  br)
    build
    run "${@:2}"
    ;;
  make)
    configure
    build
    run "${@:2}"
    ;;
  test-config)
    configure_test
    ;;
  test)
    run_test
    ;;
  lsp)
    configure_lsp
    ;;
  *)
    print_usage
    ;;
esac
