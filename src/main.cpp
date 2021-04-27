#include <DXFeed.h>
#include <chrono>
#include <iostream>
#include <thread>

int main() {
  dxf_connection_t con = nullptr;
  auto result = dxf_create_connection("demo.dxfeed.com:7300", nullptr, nullptr,
                                      nullptr, nullptr, nullptr, &con);

  if (result == DXF_FAILURE) {
    return -1;
  }

  dxf_snapshot_t snap = nullptr;
  result = dxf_create_order_snapshot(con, L"IBM", "NTV", 1, &snap);

  if (result == DXF_FAILURE) {
    dxf_close_connection(con);

    return -1;
  }

  result = dxf_attach_snapshot_listener(
      snap,
      [](auto snapshotData, void *) {
        std::cout << snapshotData->records_count << std::endl;
      },
      nullptr);

  if (result == DXF_FAILURE) {
    dxf_close_snapshot(snap);
    dxf_close_connection(con);

    return -1;
  }

  using namespace std::chrono_literals;
  std::this_thread::sleep_for(1min);

  return 0;
}