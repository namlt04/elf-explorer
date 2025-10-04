#include <gtk/gtk.h>

#include "elf.h"
#include "header.h"
#include "program.h"
#include <glib.h>
#include "section.h"
#include "dynamic.h"

GtkWidget *window;
GtkWidget *hpaned;
GtkWidget *left_frame, *right_frame;


gboolean isOpenFile = false;
GtkWidget *open_item, *close_item, *exit_item;





// left_frame 
GtkTreeStore* left_frame_store;
GtkWidget* left_frame_tree_view;
GtkCellRenderer* left_frame_renderer;
GtkTreeViewColumn* left_frame_column;
GtkWidget* left_frame_scroll;
GtkTreeIter left_frame_iter, left_frame_child, metadataIter;

// right_frame

GtkListStore* right_frame_store;
GtkWidget* right_frame_tree_view;
GtkCellRenderer* right_frame_renderer; 
GtkTreeViewColumn* right_frame_column; 
GtkWidget* right_frame_scroll;
GtkTreeIter right_frame_iter;






FILE* g_file; 
MElf_Ehdr* g_elf_header = NULL;

void focus_metadata()
{
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(left_frame_tree_view));
    GtkTreePath *path = gtk_tree_model_get_path(GTK_TREE_MODEL(left_frame_store), &metadataIter);
    gtk_tree_selection_select_path(selection, path);
    gtk_tree_view_set_cursor(GTK_TREE_VIEW(left_frame_tree_view), path, NULL, FALSE);
    gtk_tree_path_free(path);
}
void show_info_dialog(GtkWidget* parent, const char* title, const char* message)
{
    GtkWidget* dialog;
    dialog = gtk_message_dialog_new(
        GTK_WINDOW(parent),
        (GtkDialogFlags) (GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT),
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "%s", message
    );
    gtk_window_set_title(GTK_WINDOW(dialog),title);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

gboolean init_elf_header()
{
    g_elf_header = read_header_file(g_file);
    if (!g_elf_header)
    {
        show_info_dialog(window, "Thông báo", "Vui lòng chọn file .ELF để xem tính năng này");
        return TRUE;
    }
    return FALSE;
}

void destroy_right_frame()
{
    gtk_widget_destroy(right_frame_scroll); 
    right_frame_scroll = NULL;
    right_frame_store = NULL; 
    right_frame_tree_view = NULL;
}
void init_right_frame(gchar* name)
{
    destroy_right_frame();
    right_frame_renderer = gtk_cell_renderer_text_new();

    if (g_strcmp0(name, "METADATA") == 0)
    {
        right_frame_store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
            
        right_frame_tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(right_frame_store));
        gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(right_frame_tree_view), GTK_TREE_VIEW_GRID_LINES_BOTH);
     
        GtkTreeViewColumn *attribute = gtk_tree_view_column_new_with_attributes("Attribute", right_frame_renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(right_frame_tree_view), attribute);
            
        GtkTreeViewColumn *value = gtk_tree_view_column_new_with_attributes("Value", right_frame_renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(right_frame_tree_view), value); 


        } else if ( g_strcmp0(name, "ELF Header") == 0)
        {
             
            right_frame_store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);

            right_frame_tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(right_frame_store));
            gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(right_frame_tree_view), GTK_TREE_VIEW_GRID_LINES_BOTH);

            if ( !g_elf_header)
                if (init_elf_header()) 
                {
                    focus_metadata(); 
                    return;
                }

            MEhdr_Print* header = display_elf_header(g_elf_header);
            gtk_list_store_insert_with_values(right_frame_store, &right_frame_iter, -1, 0, "Magic", 1,header->s_magic); 
            gtk_list_store_insert_with_values(right_frame_store, &right_frame_iter, -1, 0, "Class", 1,header->s_class); 
            gtk_list_store_insert_with_values(right_frame_store, &right_frame_iter, -1, 0, "Data", 1,header->s_data); 
            gtk_list_store_insert_with_values(right_frame_store, &right_frame_iter, -1, 0, "Version", 1,header->s_version); 
            gtk_list_store_insert_with_values(right_frame_store, &right_frame_iter, -1, 0, "OS/ABI", 1,header->s_osabi); 
            gtk_list_store_insert_with_values(right_frame_store, &right_frame_iter, -1, 0, "ABI Version", 1,header->s_abiversion); 
            gtk_list_store_insert_with_values(right_frame_store, &right_frame_iter, -1, 0, "Type", 1,header->s_type); 
            gtk_list_store_insert_with_values(right_frame_store, &right_frame_iter, -1, 0, "Machine", 1,header->s_machine); 
            gtk_list_store_insert_with_values(right_frame_store, &right_frame_iter, -1, 0, "Version", 1,header->s_version0); 
            gtk_list_store_insert_with_values(right_frame_store, &right_frame_iter, -1, 0, "Entry Point Address", 1,header->s_entrypoint_address); 
            gtk_list_store_insert_with_values(right_frame_store, &right_frame_iter, -1, 0, "Start of program headers", 1,header->s_start_of_program_header); 
            gtk_list_store_insert_with_values(right_frame_store, &right_frame_iter, -1, 0, "Start of section headers", 1,header->s_start_of_section_header); 
            gtk_list_store_insert_with_values(right_frame_store, &right_frame_iter, -1, 0, "Flags", 1,header->s_flags); 
            gtk_list_store_insert_with_values(right_frame_store, &right_frame_iter, -1, 0, "Size of this header", 1,header->s_size_of_this_header); 
            gtk_list_store_insert_with_values(right_frame_store, &right_frame_iter, -1, 0, "Size of program headers", 1,header->s_size_of_program_header); 
            gtk_list_store_insert_with_values(right_frame_store, &right_frame_iter, -1, 0, "Number of program headers", 1,header->s_number_of_program_header); 
            gtk_list_store_insert_with_values(right_frame_store, &right_frame_iter, -1, 0, "Size of section headers", 1,header->s_size_of_section_header); 
            gtk_list_store_insert_with_values(right_frame_store, &right_frame_iter, -1, 0, "Number of section headers", 1,header->s_number_of_section_header); 
            gtk_list_store_insert_with_values(right_frame_store, &right_frame_iter, -1, 0, "Section header string table index", 1,header->s_section_header_string_table_index);



            free(header); // Cuối cùng giải phóng chính struct
            
 

            GtkTreeViewColumn *attribute = gtk_tree_view_column_new_with_attributes("Attribute", right_frame_renderer, "text", 0, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(right_frame_tree_view), attribute);
            
            GtkTreeViewColumn *value = gtk_tree_view_column_new_with_attributes("Value", right_frame_renderer, "text", 1, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(right_frame_tree_view), value);

   
        } else if ( g_strcmp0(name, "Section Header") == 0 )
        {

            // call toi ham de lay gia tri
            right_frame_store = gtk_list_store_new(10, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

            right_frame_tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(right_frame_store));
            gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(right_frame_tree_view), GTK_TREE_VIEW_GRID_LINES_BOTH);


            if ( !g_elf_header)
                if (init_elf_header())
                {   
                    focus_metadata();
                    return;
                }
            MElf_Shdr_Print** arrays = display_section_header(g_file, g_elf_header);
            for(int i = 0; i < g_elf_header->e_shnum; i++)
            {
                MElf_Shdr_Print* entity =  (MElf_Shdr_Print*) arrays[i];
                gtk_list_store_insert_with_values(right_frame_store, &right_frame_iter, -1,
                                                    0, entity->s_name, 
                                                    1, entity->s_type,
                                                    2, entity->s_addr,
                                                    3, entity->s_offset,  
                                                    4, entity->s_size, 
                                                    5, entity->s_entsize,
                                                    6, entity->s_flags, 
                                                    7, entity->s_link, 
                                                    8, entity->s_info, 
                                                    9, entity->s_addralign
                );
            }

            GtkTreeViewColumn *name = gtk_tree_view_column_new_with_attributes("Name", right_frame_renderer, "text", 0, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(right_frame_tree_view), name);
            
            GtkTreeViewColumn *type = gtk_tree_view_column_new_with_attributes("Type", right_frame_renderer, "text", 1, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(right_frame_tree_view), type); 

            GtkTreeViewColumn *address = gtk_tree_view_column_new_with_attributes("Address", right_frame_renderer, "text", 2, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(right_frame_tree_view), address);
            
            GtkTreeViewColumn *offset = gtk_tree_view_column_new_with_attributes("Offset", right_frame_renderer, "text", 3, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(right_frame_tree_view), offset);

            GtkTreeViewColumn *size = gtk_tree_view_column_new_with_attributes("Size", right_frame_renderer, "text", 4, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(right_frame_tree_view), size);
            
            GtkTreeViewColumn *entSize = gtk_tree_view_column_new_with_attributes("EntSize", right_frame_renderer, "text", 5, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(right_frame_tree_view), entSize);

            GtkTreeViewColumn *flags = gtk_tree_view_column_new_with_attributes("flags", right_frame_renderer, "text", 6, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(right_frame_tree_view), flags);
            
            GtkTreeViewColumn *link = gtk_tree_view_column_new_with_attributes("Link", right_frame_renderer, "text", 7, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(right_frame_tree_view), link);

            GtkTreeViewColumn *info = gtk_tree_view_column_new_with_attributes("Info", right_frame_renderer, "text", 8, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(right_frame_tree_view), info);
            
            GtkTreeViewColumn *align = gtk_tree_view_column_new_with_attributes("Align", right_frame_renderer, "text", 9, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(right_frame_tree_view), align);



        } else if ( g_strcmp0( name, "Program Header") == 0)
        {

            right_frame_store = gtk_list_store_new(8, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
            right_frame_tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(right_frame_store));
            gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(right_frame_tree_view), GTK_TREE_VIEW_GRID_LINES_BOTH);
            if ( !g_elf_header)
                if (init_elf_header()) 
                {
                    focus_metadata();
                    return;
                }
            MElf_Phdr_Print** arrays = display_program_header(g_file, g_elf_header);

            for(int i = 0; i < g_elf_header->e_phnum; i++)
            {
                MElf_Phdr_Print* entity =  (MElf_Phdr_Print*) arrays[i];
                gtk_list_store_insert_with_values(right_frame_store, &right_frame_iter, -1,
                                                    0, entity->s_type, 
                                                    1, entity->s_offset,
                                                    2, entity->s_vaddr,
                                                    3, entity->s_paddr,  
                                                    4, entity->s_filesz, 
                                                    5, entity->s_memsz,
                                                    6, entity->s_flags, 
                                                    7, entity->s_align
                );
                free(entity->s_type);        
                free(entity->s_offset);      
                free(entity->s_vaddr);      
                free(entity->s_paddr);          

                free(entity->s_filesz);      
                free(entity->s_align); 
                free(entity->s_memsz) ;  
                free(entity->s_flags);    

                free(entity);
            }

            GtkTreeViewColumn *type = gtk_tree_view_column_new_with_attributes("Type", right_frame_renderer, "text", 0, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(right_frame_tree_view), type);
            
            GtkTreeViewColumn *offset = gtk_tree_view_column_new_with_attributes("Offset", right_frame_renderer, "text", 1, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(right_frame_tree_view), offset); 

            GtkTreeViewColumn *virt_addr = gtk_tree_view_column_new_with_attributes("VirtAddr", right_frame_renderer, "text", 2, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(right_frame_tree_view), virt_addr);
            
            GtkTreeViewColumn *phys_addr = gtk_tree_view_column_new_with_attributes("PhysAddr", right_frame_renderer, "text", 3, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(right_frame_tree_view), phys_addr);

            GtkTreeViewColumn *file_siz = gtk_tree_view_column_new_with_attributes("FileSiz", right_frame_renderer, "text", 4, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(right_frame_tree_view), file_siz);
            
            GtkTreeViewColumn *mem_siz = gtk_tree_view_column_new_with_attributes("MemSiz", right_frame_renderer, "text", 5, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(right_frame_tree_view), mem_siz);

            GtkTreeViewColumn *flags = gtk_tree_view_column_new_with_attributes("flags", right_frame_renderer, "text", 6, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(right_frame_tree_view), flags);
            
            
            GtkTreeViewColumn *align = gtk_tree_view_column_new_with_attributes("Align", right_frame_renderer, "text", 7, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(right_frame_tree_view), align);
        } else if ( g_strcmp0(name, "Load Library") == 0)
        {
            right_frame_store = gtk_list_store_new(3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
            right_frame_tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(right_frame_store));
            gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(right_frame_tree_view), GTK_TREE_VIEW_GRID_LINES_BOTH);

            if ( !g_elf_header)
                if (init_elf_header())
                {   
                    focus_metadata();
                    return;
                }
            MElf_Phdr** program_headers = read_program_header(g_file,g_elf_header->e_ident[EI_CLASS] == ELFCLASS64, g_elf_header->e_phnum, g_elf_header->e_phoff);
            MElf_Dyn_Print** arrays = display_load_library(g_file, g_elf_header, program_headers);
            for(int i = 0; i < 28; i++)
            {
                MElf_Dyn_Print* entity =  (MElf_Dyn_Print*) arrays[i];
                gtk_list_store_insert_with_values(right_frame_store, &right_frame_iter, -1,
                                                    0, entity->tag, 
                                                    1, entity->type,
                                                    2, entity->name
                );
            }

            GtkTreeViewColumn *tag = gtk_tree_view_column_new_with_attributes("Tag", right_frame_renderer, "text", 0, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(right_frame_tree_view),tag);
            
            GtkTreeViewColumn *type = gtk_tree_view_column_new_with_attributes("Type", right_frame_renderer, "text", 1, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(right_frame_tree_view), type); 

            GtkTreeViewColumn *name = gtk_tree_view_column_new_with_attributes("Name", right_frame_renderer, "text", 2, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(right_frame_tree_view), name);
            
            

        }

    right_frame_scroll = gtk_scrolled_window_new(NULL, NULL); 
    gtk_container_add(GTK_CONTAINER(right_frame_scroll), right_frame_tree_view);
    gtk_container_add(GTK_CONTAINER(right_frame), right_frame_scroll);

}
void on_tree_selection_changed(GtkTreeView *tree_view, gpointer user_data) {
    GtkTreeSelection *selection;
    GtkTreeModel *model;
    GtkTreeIter iter;

    selection = gtk_tree_view_get_selection(tree_view); // Chon trong tree view
    
    GtkWidget *old_child = gtk_bin_get_child(GTK_BIN(right_frame));
    if (old_child) {
        gtk_widget_destroy(old_child);
    }
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) 
    {
        gchar *name = NULL; 
        gtk_tree_model_get(model, &iter, 0, &name, -1);
        init_right_frame(name); 

    }

    gtk_widget_show_all(right_frame);
}

void init_left_frame()
{
    
    left_frame_store = gtk_tree_store_new(1, G_TYPE_STRING);
    gtk_tree_store_append(left_frame_store, &metadataIter, NULL);
    gtk_tree_store_set(left_frame_store, &metadataIter, 0, "METADATA", -1);

    gtk_tree_store_append(left_frame_store, &left_frame_iter, NULL);
    gtk_tree_store_set(left_frame_store, &left_frame_iter, 0, "ELF STRUCTURE", -1);

    gtk_tree_store_append(left_frame_store, &left_frame_child, &left_frame_iter);
    gtk_tree_store_set(left_frame_store, &left_frame_child, 0, "ELF Header", -1);

    gtk_tree_store_append(left_frame_store, &left_frame_child, &left_frame_iter);
    gtk_tree_store_set(left_frame_store, &left_frame_child, 0, "Program Header", -1);

    gtk_tree_store_append(left_frame_store, &left_frame_child, &left_frame_iter);
    gtk_tree_store_set(left_frame_store, &left_frame_child, 0, "Section Header", -1);

    gtk_tree_store_append(left_frame_store, &left_frame_iter, NULL);
    gtk_tree_store_set(left_frame_store, &left_frame_iter, 0, "Load Library", -1);

    left_frame_tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(left_frame_store));
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(left_frame_tree_view), FALSE);

    left_frame_renderer = gtk_cell_renderer_text_new();
    left_frame_column = gtk_tree_view_column_new_with_attributes("Key", left_frame_renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(left_frame_tree_view), left_frame_column);

    left_frame_scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(left_frame_scroll), left_frame_tree_view);

    gtk_container_add(GTK_CONTAINER(left_frame), left_frame_scroll);
    // Kết nối tree selection
    g_signal_connect(left_frame_tree_view, "cursor-changed", G_CALLBACK(on_tree_selection_changed), NULL);
    gtk_widget_show_all(left_frame);

    // ----- Thiet lap mac dinh, nhay vao metadata
    focus_metadata();
}



void destroy_left_frame()
{
    gtk_widget_destroy(left_frame_scroll);
    left_frame_scroll = NULL;

}





// ---- handle click on menu bar
void on_close_activate(GtkMenuItem *menuitem, gpointer user_data) {

    g_file = NULL; 
    g_elf_header = NULL;
    // Neu dong thanh cong moi doi trang thai
    isOpenFile = !isOpenFile;
    gtk_widget_set_sensitive(open_item, !isOpenFile);
    gtk_widget_set_sensitive(close_item, isOpenFile);

    destroy_right_frame(); 
    destroy_left_frame();

}
void on_open_activate(GtkMenuItem *menuitem, gpointer user_data) {

    GtkWidget *parent_window = GTK_WIDGET(user_data); // lấy window cha
    GtkWidget *dialog = gtk_file_chooser_dialog_new(
        "Open File",
        GTK_WINDOW(parent_window),
        GTK_FILE_CHOOSER_ACTION_OPEN,
        "_Cancel", GTK_RESPONSE_CANCEL,
        "_Open", GTK_RESPONSE_ACCEPT,
        NULL
    );

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        if(isOpenFile)
            on_close_activate(menuitem, user_data);
        g_file = fopen(filename, "rb");
        // Neu nhu mo thanh cong
        init_left_frame();
        isOpenFile = !isOpenFile; // Dang dong -> mo
        gtk_widget_set_sensitive(open_item, isOpenFile);
        gtk_widget_set_sensitive(close_item, isOpenFile);
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}
void on_exit_activate(GtkMenuItem *menuitem, gpointer user_data) {
    gtk_main_quit();
}

// ---- main
int main(int argc, char *argv[]) {

    gtk_init(&argc, &argv);
    // ---- Init Window 
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "ELF Explorer");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // ---- Init Menubar  
    GtkWidget *menubar = gtk_menu_bar_new();
    GtkWidget *file_menu = gtk_menu_new();
    GtkWidget *file_item = gtk_menu_item_new_with_label("File");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_item), file_menu);

    open_item = gtk_menu_item_new_with_label("Open");
    g_signal_connect(open_item, "activate", G_CALLBACK(on_open_activate), window);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), open_item);

    close_item = gtk_menu_item_new_with_label("Close");
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), close_item);
    g_signal_connect(close_item, "activate", G_CALLBACK(on_close_activate), window);
    exit_item = gtk_menu_item_new_with_label("Exit");
    g_signal_connect(exit_item, "activate", G_CALLBACK(on_exit_activate), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), exit_item);
    // Thiet lap trang thai cua tung item
    gtk_widget_set_sensitive(open_item, !isOpenFile);
    gtk_widget_set_sensitive(close_item, isOpenFile);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_item);

    // --- split workspace
    hpaned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);

    // Left frame
    left_frame = gtk_frame_new("");
    gtk_widget_set_size_request(left_frame, 240, -1);
    gtk_paned_pack1(GTK_PANED(hpaned), left_frame, TRUE, FALSE);

    // Right frame
    right_frame = gtk_frame_new("");
    gtk_widget_set_size_request(right_frame, 560, -1);
    gtk_paned_pack2(GTK_PANED(hpaned), right_frame, TRUE, FALSE);

    
    


    // Layout
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hpaned, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);




    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
