//$Id$ -*- c++ -*-

/* gtkmm example Copyright (C) 2002 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "dndwindow.h"
#include <iostream>

DnDWindow::DnDWindow()
: m_Button_Drag("Drag Here\n"),
  m_Label_Drop("Drop here\n")
{
  set_title("DnD example");

  add(m_HBox);

  //Targets:
  std::list<Gtk::TargetEntry> listTargets;
  listTargets.push_back( Gtk::TargetEntry("STRING") );
  listTargets.push_back( Gtk::TargetEntry("text/plain") );

  //Drag site:

  //Make m_Button_Drag a DnD drag source:
  m_Button_Drag.drag_source_set(listTargets);
		
  //Connect signals:
  m_Button_Drag.signal_drag_data_get().connect( SigC::slot(*this, &DnDWindow::on_button_drag_data_get));

  m_HBox.pack_start(m_Button_Drag);

  //Drop site:

  //Make m_Label_Drop a DnD drop destination:
  m_Label_Drop.drag_dest_set(listTargets);

  //Connect signals:
  m_Label_Drop.signal_drag_data_received().connect( SigC::slot(*this, &DnDWindow::on_label_drop_drag_data_received) );

  m_HBox.pack_start(m_Label_Drop);

  show_all();
}

DnDWindow::~DnDWindow()
{
}

void DnDWindow::on_button_drag_data_get(const Glib::RefPtr<Gdk::DragContext>&, GtkSelectionData* selection_data, guint, guint)
{
  //TODO: The gtkmm API needs to change to use a Gtk::SelectionData instead of a GtkSelectionData.
  //That should happen for gtkmm 2.4.
  
  gtk_selection_data_set (selection_data, selection_data->target, 8, (const guchar*)"I'm Data!", 9);
}

void DnDWindow::on_label_drop_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int, int, GtkSelectionData* selection_data, guint, guint time)
{
  //TODO: The gtkmm API needs to change to use a Gtk::SelectionData instead of a GtkSelectionData.
  //That should happen for gtkmm 2.4.
  
  if ((selection_data->length >= 0) && (selection_data->format == 8))
  {
    std::cout << "Received \"" << (gchar *)(selection_data->data) << "\" in label " << std::endl;
  }

  context->drag_finish(false, false, time);
}
