#ifndef __MONO_DEBUG_MONO_SYMFILE_H__
#define __MONO_DEBUG_MONO_SYMFILE_H__

#include <glib.h>
#include <mono/metadata/class.h>
#include <mono/metadata/reflection.h>
#include <mono/metadata/mono-debug.h>

typedef struct MonoSymbolFileOffsetTable	MonoSymbolFileOffsetTable;
typedef struct MonoSymbolFileLineNumberEntry	MonoSymbolFileLineNumberEntry;
typedef struct MonoSymbolFileMethodEntry	MonoSymbolFileMethodEntry;
typedef struct MonoSymbolFileMethodAddress	MonoSymbolFileMethodAddress;
typedef struct MonoSymbolFileDynamicTable	MonoSymbolFileDynamicTable;
typedef struct MonoSymbolFileSourceEntry	MonoSymbolFileSourceEntry;
typedef struct MonoSymbolFileMethodIndexEntry	MonoSymbolFileMethodIndexEntry;
typedef struct MonoSymbolFileLexicalBlockEntry	MonoSymbolFileLexicalBlockEntry;

typedef struct MonoDebugMethodInfo		MonoDebugMethodInfo;
typedef struct MonoDebugLexicalBlockEntry	MonoDebugLexicalBlockEntry;
typedef struct MonoDebugLineNumberEntry		MonoDebugLineNumberEntry;

/* Keep in sync with OffsetTable in mcs/class/Mono.CSharp.Debugger/MonoSymbolTable.cs */
struct MonoSymbolFileOffsetTable {
	guint32 total_file_size;
	guint32 data_section_offset;
	guint32 data_section_size;
	guint32 source_count;
	guint32 source_table_offset;
	guint32 source_table_size;
	guint32 method_count;
	guint32 method_table_offset;
	guint32 method_table_size;
	guint32 type_count;
};

struct MonoSymbolFileMethodEntry {
	guint32 source_index;
	guint32 token;
	guint32 start_row;
	guint32 end_row;
	guint32 class_type_index;
	guint32 num_parameters;
	guint32 num_locals;
	guint32 num_line_numbers;
	guint32 name_offset;
	guint32 full_name_offset;
	guint32 type_index_table_offset;
	guint32 local_variable_table_offset;
	guint32 line_number_table_offset;
	guint32 num_lexical_blocks;
	guint32 lexical_block_table_offset;
	guint32 namespace_idx;
	guint32 local_names_ambiguous;
};

struct MonoSymbolFileSourceEntry {
	guint32 index;
	guint32 num_methods;
	guint32 num_namespaces;
	guint32 name_offset;
	guint32 method_offset;
	guint32 nstable_offset;
};

struct MonoSymbolFileMethodIndexEntry {
	guint32 file_offset;
	guint32 full_name_offset;
	guint32 token;
};

struct MonoSymbolFileMethodAddress {
	guint32 size;
	const guint8 *start_address;
	const guint8 *end_address;
	const guint8 *method_start_address;
	const guint8 *method_end_address;
	const guint8 *wrapper_address;
	guint32 has_this;
	guint32 variable_table_offset;
	guint32 type_table_offset;
	guint32 num_line_numbers;
	guint32 line_number_offset;
	guint32 lexical_block_table_offset;
	guint8 data [MONO_ZERO_LEN_ARRAY];
};

struct MonoSymbolFileLexicalBlockEntry {
	guint32 start_offset;
	guint32 end_offset;
};

struct MonoSymbolFileLineNumberEntry {
	guint32 row;
	guint32 offset;
};

struct MonoDebugMethodInfo {
	MonoMethod *method;
	MonoDebugHandle *handle;
	guint32 index;
	guint32 num_il_offsets;
	MonoSymbolFileLineNumberEntry *il_offsets;
	MonoSymbolFileMethodEntry *entry;
};

struct MonoDebugLexicalBlockEntry {
	guint32 start_address;
	guint32 end_address;
};

struct MonoDebugLineNumberEntry {
	guint32 offset;
	guint32 address;
};

struct _MonoSymbolFile {
	const guint8 *raw_contents;
	int raw_contents_size;
	GHashTable *method_hash;
	MonoSymbolFileOffsetTable *offset_table;
};

#define MONO_SYMBOL_FILE_VERSION		35
#define MONO_SYMBOL_FILE_MAGIC			0x45e82623fd7fa614

MonoSymbolFile *
mono_debug_open_mono_symbol_file   (MonoDebugHandle           *handle,
				    gboolean                   create_symfile);

void
mono_debug_close_mono_symbol_file  (MonoSymbolFile           *symfile);

gchar *
mono_debug_find_source_location    (MonoSymbolFile           *symfile,
				    MonoMethod               *method,
				    guint32                   offset,
				    guint32                  *line_number);

gint32
_mono_debug_address_from_il_offset (MonoDebugMethodJitInfo   *jit,
				    guint32                   il_offset);

MonoDebugMethodInfo *
mono_debug_find_method             (MonoSymbolFile           *symfile,
				    MonoMethod               *method);

#endif /* __MONO_SYMFILE_H__ */

