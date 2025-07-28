#pragma once
#include "ui.h"
#include <QStandardItemModel>
#include <QTableView>
#include <QVBoxLayout>

class MemUI : public UI {
public:
  MemUI(QWidget *parent = nullptr) : UI(parent) {
    model.setColumnCount(1);
    model.setVerticalHeaderLabels(
        {// 内存基础信息
         "mem_total", "mem_free", "mem_available", "buffers", "cached",
         "swap_cached", "active", "inactive",

         // 匿名/文件页
         "active_anon", "inactive_anon", "active_file", "inactive_file",
         "unevictable", "mlocked",

         // Swap信息
         "swap_total", "swap_free",

         // 写回相关
         "dirty", "writeback", "writeback_tmp",

         // 内存使用细分
         "anon_pages", "mapped", "shmem",

         // 内核内存
         "k_reclaimable", "slab", "s_reclaimable", "s_unreclaim",
         "kernel_stack", "page_tables", "sec_page_tables",

         // 其他
         "nfs_unstable", "bounce",

         // 内存限制
         "commit_limit", "committed_as",

         // 虚拟内存
         "vmalloc_total", "vmalloc_used", "vmalloc_chunk",

         // CPU内存
         "percpu",

         // 硬件相关
         "hardware_corrupted",

         // 大页
         "anon_huge_pages", "shmem_huge_pages", "shmem_pmd_mapped",
         "file_huge_pages", "file_pmd_mapped",

         // 大页配置
         "huge_pages_total", "huge_pages_free", "huge_pages_rsvd",
         "huge_pages_surp", "hugepagesize", "hugetlb",

         // 直接映射
         "direct_map_4k", "direct_map_2m", "direct_map_1g"});
    tableView.setModel(&model);
    tableView.setEditTriggers(QAbstractItemView::NoEditTriggers);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(&tableView);
    setWindowTitle("Memory");
    resize(400, 1000);
  }

  void refresh(Monitor::MonitorInfo *info) override {
    auto load_info = info->mem_info();
    model.setItem(0, 0,
                  new QStandardItem(QString::number(load_info.mem_total())));
    model.setItem(1, 0,
                  new QStandardItem(QString::number(load_info.mem_free())));
    model.setItem(
        2, 0, new QStandardItem(QString::number(load_info.mem_available())));
    model.setItem(3, 0,
                  new QStandardItem(QString::number(load_info.buffers())));
    model.setItem(4, 0, new QStandardItem(QString::number(load_info.cached())));
    model.setItem(5, 0,
                  new QStandardItem(QString::number(load_info.swap_cached())));
    model.setItem(6, 0, new QStandardItem(QString::number(load_info.active())));
    model.setItem(7, 0,
                  new QStandardItem(QString::number(load_info.inactive())));
    model.setItem(8, 0,
                  new QStandardItem(QString::number(load_info.active_anon())));
    model.setItem(
        9, 0, new QStandardItem(QString::number(load_info.inactive_anon())));
    model.setItem(10, 0,
                  new QStandardItem(QString::number(load_info.active_file())));
    model.setItem(
        11, 0, new QStandardItem(QString::number(load_info.inactive_file())));
    model.setItem(12, 0,
                  new QStandardItem(QString::number(load_info.unevictable())));
    model.setItem(13, 0,
                  new QStandardItem(QString::number(load_info.mlocked())));
    model.setItem(14, 0,
                  new QStandardItem(QString::number(load_info.swap_total())));
    model.setItem(15, 0,
                  new QStandardItem(QString::number(load_info.swap_free())));
    model.setItem(16, 0, new QStandardItem(QString::number(load_info.dirty())));
    model.setItem(17, 0,
                  new QStandardItem(QString::number(load_info.writeback())));
    model.setItem(18, 0,
                  new QStandardItem(QString::number(load_info.anon_pages())));
    model.setItem(19, 0,
                  new QStandardItem(QString::number(load_info.mapped())));
    model.setItem(20, 0, new QStandardItem(QString::number(load_info.shmem())));
    model.setItem(
        21, 0, new QStandardItem(QString::number(load_info.k_reclaimable())));
    model.setItem(22, 0, new QStandardItem(QString::number(load_info.slab())));
    model.setItem(
        23, 0, new QStandardItem(QString::number(load_info.s_reclaimable())));
    model.setItem(24, 0,
                  new QStandardItem(QString::number(load_info.s_unreclaim())));
    model.setItem(25, 0,
                  new QStandardItem(QString::number(load_info.kernel_stack())));
    model.setItem(26, 0,
                  new QStandardItem(QString::number(load_info.page_tables())));
    model.setItem(
        27, 0, new QStandardItem(QString::number(load_info.sec_page_tables())));
    model.setItem(28, 0,
                  new QStandardItem(QString::number(load_info.nfs_unstable())));
    model.setItem(29, 0,
                  new QStandardItem(QString::number(load_info.bounce())));
    model.setItem(
        30, 0, new QStandardItem(QString::number(load_info.writeback_tmp())));
    model.setItem(31, 0,
                  new QStandardItem(QString::number(load_info.commit_limit())));
    model.setItem(32, 0,
                  new QStandardItem(QString::number(load_info.committed_as())));
    model.setItem(
        33, 0, new QStandardItem(QString::number(load_info.vmalloc_total())));
    model.setItem(34, 0,
                  new QStandardItem(QString::number(load_info.vmalloc_used())));
    model.setItem(
        35, 0, new QStandardItem(QString::number(load_info.vmalloc_chunk())));
    model.setItem(36, 0,
                  new QStandardItem(QString::number(load_info.percpu())));
    model.setItem(
        37, 0,
        new QStandardItem(QString::number(load_info.hardware_corrupted())));
    model.setItem(
        38, 0, new QStandardItem(QString::number(load_info.anon_huge_pages())));
    model.setItem(
        39, 0,
        new QStandardItem(QString::number(load_info.shmem_huge_pages())));
    model.setItem(
        40, 0,
        new QStandardItem(QString::number(load_info.shmem_pmd_mapped())));
    model.setItem(
        41, 0, new QStandardItem(QString::number(load_info.file_huge_pages())));
    model.setItem(
        42, 0, new QStandardItem(QString::number(load_info.file_pmd_mapped())));
    model.setItem(
        43, 0,
        new QStandardItem(QString::number(load_info.huge_pages_total())));
    model.setItem(
        44, 0, new QStandardItem(QString::number(load_info.huge_pages_free())));
    model.setItem(
        45, 0, new QStandardItem(QString::number(load_info.huge_pages_rsvd())));
    model.setItem(
        46, 0, new QStandardItem(QString::number(load_info.huge_pages_surp())));
    model.setItem(47, 0,
                  new QStandardItem(QString::number(load_info.hugepagesize())));
    model.setItem(48, 0,
                  new QStandardItem(QString::number(load_info.hugetlb())));
    model.setItem(
        49, 0, new QStandardItem(QString::number(load_info.direct_map_4k())));
    model.setItem(
        50, 0, new QStandardItem(QString::number(load_info.direct_map_2m())));
    model.setItem(
        51, 0, new QStandardItem(QString::number(load_info.direct_map_1g())));
  }

private:
  QStandardItemModel model;
  QTableView tableView;
};