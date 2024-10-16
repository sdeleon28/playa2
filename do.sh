function print_usage() {
  echo ""
  echo "SYNOPSIS"
  echo ""
  echo "  ./do.sh [
      |config
      |build
      |run
      |make: config, build and run
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
  make)
    configure
    build
    run
    ;;
  *)
    print_usage
    ;;
esac
