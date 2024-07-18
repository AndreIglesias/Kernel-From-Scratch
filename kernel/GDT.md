## Global Descriptor Table (GDT) Structure and Explanation

### Segment Descriptor Layout
<div style="text-align: center;">
  <table style="margin: 0 auto;">
    <tr>
      <th colspan="5">Segment Descriptor</th>
    </tr>
    <tr>
      <th>63 - 56</th>
      <th>55 - 52</th>
      <th>51 - 48</th>
      <th>47 - 40</th>
      <th>39 - 32</th>
    </tr>
    <tr>
      <td>Base (31-24)</td>
      <td>Flags (3-0)</td>
      <td>Limit (19-16)</td>
      <td>Access Byte (7-0)</td>
      <td>Base (23-16)</td>
    </tr>
    <tr>
      <th colspan="2">31 - 16</th>
      <th colspan="3">15 - 0</th>
    </tr>
    <tr>
      <td colspan="2">Base (15-0)</td>
      <td colspan="3">Limit (15-0)</td>
    </tr>
  </table>
</div>

#### GDT Structure

|Type| Segment Descriptor | GDT Position |
|--| :----------------: | :----------: |
|🟩| Limit (15-0)       | 15 - 0       |
|🟦| Base (15-0)        | 31 - 16      |
|🟦| Base (23-16)       | 39 - 32      |
|🟧| Access Byte (7-0)  | 47 - 40      |
|🟩| Limit (19-16)      | 51 - 48      |
|🟫| Flags (3-0)        | 55 - 52      |
|🟦| Base (31-24)       | 63 - 56      |

##### C structure

```C
typedef struct s_gdt_descriptor {
	uint16_t limit_low;    // 16 bits of limit
	uint16_t base_low;     // 16 bits of base
	uint8_t base_mid;      // 8 bits of base
	uint8_t access;        // 8 bits off access byte
	uint8_t limit_high :4; // 4 bits of limit
	uint8_t flags :4;      // 4 bits of flags
	uint8_t base_high;     // last 8 bits of base
} __attribute__((packed)) gdt_descriptor;

```

### Explanation of Fields

#### Base Address
- The base address is a 32-bit value that specifies the starting address of the segment in the linear address space.

The full base address is composed as follows:

- Maximum Value: `0xFFFFFFFF` (4,294,967,295 in decimal)
- Minimum Value: `0x00000000` (0 in decimal)

#### Limit
- The limit specifies the size of the segment. It is a 20-bit value, allowing segments to range up to 1MB in size (or 4GB with granularity set).

The full limit value is composed as follows:

- Maximum Value: `0xFFFFF` (1,048,575 in decimal)
- Minimum Value: `0x00000` (0 in decimal)

##### Granularity

The segment limit can be interpreted differently depending on the granularity flag (G bit) in the flags field. If the granularity flag is set, the limit is multiplied by 4 KiB (4096 bytes). This means:

- With Granularity (G = 1):
    - Maximum Effective Limit: `(0xFFFFF + 1) * 4096 - 1 = 4 GiB - 1 (4,294,967,295 bytes)`
    - Minimum Effective Limit: `0 * 4096 = 0 bytes`

- Without Granularity (G = 0):
    - Maximum Effective Limit: `0xFFFFF = 1 MiB - 1 (1,048,575 bytes)`
    - Minimum Effective Limit: `0 = 0 bytes`

#### Access Byte
- The access byte is an 8-bit field that specifies the access rights and type of the segment. Its layout is as follows:
    <table>
    <tr>
        <th>7</th>
        <th>6</th>
        <th>5</th>
        <th>4</th>
        <th>3</th>
        <th>2</th>
        <th>1</th>
        <th>0</th>
    </tr>
    <tr>
        <td>P</td>
        <td colspan="2">DPL</td>
        <td>S</td>
        <td>E</td>
        <td>DC</td>
        <td>RW</td>
        <td>A</td>
    </tr>
    </table>
    
    - **P (Present bit)**: Indicates whether the segment is present in memory. 
        - 0 = not present
        - 1 = present

    - **DPL (Descriptor Privilege Level)**: Specifies the privilege level of the segment.
        - 0 = highest privilege (kernel)
        - 3 = lowest privilege (user applications)

    - **S (Descriptor Type)**: 
        - 0 = system segment
        - 1 = code or data segment

    - **E (Executable bit)**:
        - 0 = data segment
        - 1 = code segment

    - **DC (Direction bit/Conforming bit)**:
        - **Data segment**:
            - 0 = segment grows up
            - 1 = segment grows down
        - **Code segment**:
            - 0 = code can only be executed from an equal privilege level
            - 1 = code can be executed from an equal or lower privilege level

    - **RW (Readable bit/Writable bit)**:
        - **Data segment**:
            - 0 = read-only
            - 1 = readable and writable
        - **Code segment**:
            - 0 = not readable
            - 1 = readable (all code segments are not writable)
    - **A (Accessed bit)**: 
        - 0 = not accessed
        - 1 = accessed (CPU sets this bit when segment is accessed)

#### Flags

| 3 | 2 | 1 | 0 |
|---|---|---|---|
| G | DB| L |   | 

- **G (Granularity flag)**:
  - 0 = limit is in 1 byte units (byte granularity)
  - 1 = limit is in 4KB units (page granularity)

- **DB (Size flag)**:
  - 0 = 16-bit protected mode segment
  - 1 = 32-bit protected mode segment

- **L (Long-mode code flag)**:
  - 0 = other modes
  - 1 = 64-bit protected mode segment

This layout ensures that each segment in the GDT is properly defined with its base address, limit, access rights, and additional flags, enabling the CPU to manage memory segmentation efficiently.

## Defined Descriptors

The GDT is at address `0x00000800`.

- Kernel Code
- Kernel Data
- Kernel stack
- User code
- User data
- User stack

### Access Byte

```C
// Segment access byte
# define ACCESS_KERNEL  A_PRESENT(1) | A_PRIVILEGE(HIGH) | A_TYPE(CODE_DATA)
# define ACCESS_USER    A_PRESENT(1) | A_PRIVILEGE(LOW)  | A_TYPE(CODE_DATA)

# define ACCESS_CODE    A_EXECUTABLE(1) | A_DIRECTION(0) | A_READWRITE(1) | A_ACCESSED(0)
# define ACCESS_DATA    A_EXECUTABLE(0) | A_DIRECTION(0) | A_READWRITE(1) | A_ACCESSED(0)
# define ACCESS_STACK   A_EXECUTABLE(0) | A_DIRECTION(1) | A_READWRITE(1) | A_ACCESSED(0)
```

We create the **GDT** using the macros:

```C
create_descriptor(0, 0, 0, 0, 0); // Null segment
create_descriptor(1, 0, 0xFFFFF, ACCESS_KERNEL | ACCESS_CODE, GDT_FLAGS); // Kernel Code segment
create_descriptor(2, 0, 0xFFFFF, ACCESS_KERNEL | ACCESS_DATA, GDT_FLAGS); // Kernel Data segment
create_descriptor(3, 0, 0xFFFFF, ACCESS_KERNEL | ACCESS_STACK, GDT_FLAGS); // Kernel Stack segment
create_descriptor(4, 0, 0xFFFFF, ACCESS_USER | ACCESS_CODE, GDT_FLAGS); // User Code segment
create_descriptor(5, 0, 0xFFFFF, ACCESS_USER | ACCESS_DATA, GDT_FLAGS); // User Data segment
create_descriptor(6, 0, 0xFFFFF, ACCESS_USER | ACCESS_STACK, GDT_FLAGS); // User Stack segment
```
