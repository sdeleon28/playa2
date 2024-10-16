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
  cmake --build build/tui --target ftxui-starter
}

function run() {
  ./build/tui/ftxui-starter
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
  cmake --build build/tui-lsp --target ftxui-starter
}

case $1 in
  config)
    configure
    ;;
  build)
    build
    ;;
  run)
    run
    ;;
  br)
    build
    run
    ;;
  make)
    configure
    build
    run
    ;;
  lsp)
    configure_lsp
    ;;
  *)
    print_usage
    ;;
esac
