#include "base.h"

#define set_attribute(Obj, Key, Value)                                         \
  file.readLine(&line);                                                        \
  Obj->set_##Key(std::stoull(Value));                                          \
  line.clear()

void MemMonitor::update(Monitor::MonitorInfo *info) {
  File file("/proc/meminfo");
  std::vector<std::string> line;
  auto mem = info->mutable_mem_info();
  set_attribute(mem, mem_total, line[1]);
  set_attribute(mem, mem_free, line[1]);
  set_attribute(mem, mem_available, line[1]);
  set_attribute(mem, buffers, line[1]);
  set_attribute(mem, cached, line[1]);
  set_attribute(mem, swap_cached, line[1]);
  set_attribute(mem, active, line[1]);
  set_attribute(mem, inactive, line[1]);
  set_attribute(mem, active_anon, line[1]);
  set_attribute(mem, inactive_anon, line[1]);
  set_attribute(mem, active_file, line[1]);
  set_attribute(mem, inactive_file, line[1]);
  set_attribute(mem, unevictable, line[1]);
  set_attribute(mem, mlocked, line[1]);
  set_attribute(mem, swap_total, line[1]);
  set_attribute(mem, swap_free, line[1]);
  set_attribute(mem, dirty, line[1]);
  set_attribute(mem, writeback, line[1]);
  set_attribute(mem, anon_pages, line[1]);
  set_attribute(mem, mapped, line[1]);
  set_attribute(mem, shmem, line[1]);
  set_attribute(mem, k_reclaimable, line[1]);
  set_attribute(mem, slab, line[1]);
  set_attribute(mem, s_reclaimable, line[1]);
  set_attribute(mem, s_unreclaim, line[1]);
  set_attribute(mem, kernel_stack, line[1]);
  set_attribute(mem, page_tables, line[1]);
  set_attribute(mem, sec_page_tables, line[1]);
  set_attribute(mem, nfs_unstable, line[1]);
  set_attribute(mem, bounce, line[1]);
  set_attribute(mem, writeback_tmp, line[1]);
  set_attribute(mem, commit_limit, line[1]);
  set_attribute(mem, committed_as, line[1]);
  set_attribute(mem, vmalloc_total, line[1]);
  set_attribute(mem, vmalloc_used, line[1]);
  set_attribute(mem, vmalloc_chunk, line[1]);
  set_attribute(mem, percpu, line[1]);
  set_attribute(mem, hardware_corrupted, line[1]);
  set_attribute(mem, anon_huge_pages, line[1]);
  set_attribute(mem, shmem_huge_pages, line[1]);
  set_attribute(mem, shmem_pmd_mapped, line[1]);
  set_attribute(mem, file_huge_pages, line[1]);
  set_attribute(mem, file_pmd_mapped, line[1]);
  set_attribute(mem, huge_pages_total, line[1]);
  set_attribute(mem, huge_pages_free, line[1]);
  set_attribute(mem, huge_pages_rsvd, line[1]);
  set_attribute(mem, huge_pages_surp, line[1]);
  set_attribute(mem, hugepagesize, line[1]);
  set_attribute(mem, hugetlb, line[1]);
  set_attribute(mem, direct_map_4k, line[1]);
  set_attribute(mem, direct_map_2m, line[1]);
  set_attribute(mem, direct_map_1g, line[1]);
}