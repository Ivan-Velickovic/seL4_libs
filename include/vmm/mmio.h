#ifndef _VMM_MMIO_H
#define _VMM_MMIO_H

typedef struct vmm_vcpu vmm_vcpu_t;

// Deals with ranges of memory mapped io for emulated devices

typedef void (*vmm_mmio_read_fn)(vmm_vcpu_t * vcpu, void *cookie,
        uint32_t rel_addr, int size, uint32_t *result);
typedef void (*vmm_mmio_write_fn)(vmm_vcpu_t *vcpu, void *cookie,
        uint32_t rel_addr, int size, uint32_t value);

typedef struct vmm_mmio_range {
    uintptr_t start;
    uintptr_t end;

    vmm_mmio_read_fn read_handler;
    vmm_mmio_write_fn write_handler;

    void *cookie;

    const char *name;
} vmm_mmio_range_t;

typedef struct vmm_mmio_list {
    vmm_mmio_range_t *ranges; // Sorted array
    int num_ranges;
} vmm_mmio_list_t;

// Initialise
int vmm_mmio_init(vmm_mmio_list_t *list);

// Try to handle an exit with mmio
// Returns 0 if handled, or -1 otherwise
int vmm_mmio_exit_handler(vmm_vcpu_t *vcpu, uintptr_t addr, unsigned int qualification);

int vmm_mmio_add_handler(vmm_mmio_list_t *list, uintptr_t start, uintptr_t end,
        void *cookie, const char *name,
        vmm_mmio_read_fn read_handler, vmm_mmio_write_fn write_handler);

#endif

