// -*- c++ -*-
/* $Id$ */

/* 
 *
 * Copyright 1998-2002 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <gtk/gtkimagemenuitem.h>

#include <gtkmm/menu_elems.h>
#include <gtkmm/label.h>

#ifndef GTKMM_WIN32
#include <strings.h>
#endif // GTKMM_WIN32

namespace Gtk
{

namespace Menu_Helpers
{

Element::Element()
: child_(0)
{}

Element::Element(MenuItem& child)
: child_(&child)
{}

Element::~Element()
{}

void Element::set_accel_key(const AccelKey& accel_key)
{
  if(child_)
    child_->set_accel_key(accel_key);
}

const Glib::RefPtr<MenuItem>& Element::get_child() const
{
  return child_;
}

MenuElem::MenuElem(MenuItem& child)
: Element(child)
{}

MenuElem::MenuElem(const Glib::ustring& label, 
                   const CallSlot& slot)
{
  child_ = manage(new MenuItem(label, true));
  if(slot)
    child_->signal_activate().connect(slot);
  child_->show();
}

MenuElem::MenuElem(const Glib::ustring& label,
                   const AccelKey& accel_key,
                   const CallSlot& slot)
{
  child_ = manage(new MenuItem(label, true));
  if(slot)
    child_->signal_activate().connect(slot);
  set_accel_key(accel_key);
  child_->show();
}

MenuElem::MenuElem(const Glib::ustring& label, Menu& submenu)
{
  child_ = manage(new MenuItem(label, true));
  child_->set_submenu(submenu);
  child_->show();
}

MenuElem::MenuElem(const Glib::ustring& label, 
                   const AccelKey& accel_key,
                   Gtk::Menu& submenu)
{
  child_ = manage(new MenuItem(label, true));
  child_->set_submenu(submenu);
  set_accel_key(accel_key);
  child_->show();
}

SeparatorElem::SeparatorElem()
{
  child_ = manage(new SeparatorMenuItem());
  child_->show();
}

ImageMenuElem::ImageMenuElem(ImageMenuItem& child)
: Element(child)
{}

ImageMenuElem::ImageMenuElem(const Glib::ustring& label,
                             Gtk::Widget& image_widget,
                             const CallSlot& slot)
{
  image_widget.show(); //We assume that the coder wants to actually show the widget.
  child_ = manage(new ImageMenuItem(image_widget, label, true));
  if(slot)
    child_->signal_activate().connect(slot);
  child_->show();
}

ImageMenuElem::ImageMenuElem(const Glib::ustring& label,
                             const AccelKey& accel_key,
                             Gtk::Widget& image_widget,
                             const CallSlot& slot)
{
  image_widget.show(); //We assume that the coder wants to actually show the widget.
  child_ = manage(new ImageMenuItem(image_widget, label, true));
  if(slot)
    child_->signal_activate().connect(slot);
  set_accel_key(accel_key);
  child_->show();
}

ImageMenuElem::ImageMenuElem(const Glib::ustring& label,
                             Gtk::Widget& image_widget,
                             Gtk::Menu& submenu)
{
  image_widget.show(); //We assume that the coder wants to actually show the widget.
  child_ = manage(new ImageMenuItem(image_widget, label, true));
  child_->set_submenu(submenu);
  child_->show();
}

ImageMenuElem::ImageMenuElem(const Glib::ustring& label,
                             const AccelKey& accel_key,
                             Gtk::Widget& image_widget,
                             Gtk::Menu& submenu)
{
  image_widget.show(); //We assume that the coder wants to actually show the widget.
  child_ = manage(new ImageMenuItem(image_widget, label, true));
  set_accel_key(accel_key);
  child_->set_submenu(submenu);
  child_->show();
}

StockMenuElem::StockMenuElem(const Gtk::StockID& stock_id,
                             const CallSlot& slot)
{
  child_ = manage(new ImageMenuItem(stock_id));
  if(slot)
    child_->signal_activate().connect(slot);
  child_->show();
}

StockMenuElem::StockMenuElem(const Gtk::StockID& stock_id,
                             const AccelKey& accel_key,
                             const CallSlot& slot)
{
  child_ = manage(new ImageMenuItem(stock_id));
  if(slot)
    child_->signal_activate().connect(slot);
  set_accel_key(accel_key);
  child_->show();
}

StockMenuElem::StockMenuElem(const Gtk::StockID& stock_id,
                             Gtk::Menu& submenu)
{
  child_ = manage(new ImageMenuItem(stock_id));
  child_->set_submenu(submenu);
  child_->show();
}

StockMenuElem::StockMenuElem(const Gtk::StockID& stock_id,
                             const AccelKey& accel_key,
                             Gtk::Menu& submenu)
{
  child_ = manage(new ImageMenuItem(stock_id));
  set_accel_key(accel_key);
  child_->set_submenu(submenu);
  child_->show();
}

CheckMenuElem::CheckMenuElem(CheckMenuItem& child)
: Element(child)
{}

CheckMenuElem::CheckMenuElem(const Glib::ustring& label,
                             const CallSlot& slot)
{
  CheckMenuItem* item = manage(new CheckMenuItem(label, true));
  child_ = item;
  if(slot)
    item->signal_toggled().connect(slot);
  child_->show();
}

CheckMenuElem::CheckMenuElem(const Glib::ustring& label,
                             const AccelKey& accel_key,
                             const CallSlot& slot)
{
  CheckMenuItem* item = manage(new CheckMenuItem(label, true));
  child_ = item;
  set_accel_key(accel_key);
  if(slot)
    item->signal_toggled().connect(slot);
  child_->show();
}


RadioMenuElem::RadioMenuElem(RadioMenuItem& child)
: Element(child), gr_(0)
{}

RadioMenuElem::RadioMenuElem(RadioMenuItem::Group& group,
                             const Glib::ustring& label,
                             const CallSlot& slot)
  : gr_(&group)
{
  CheckMenuItem* item = manage(new RadioMenuItem(*gr_, label, true));
  child_ = item;
  if(slot)
    item->signal_toggled().connect(slot);
  child_->show();
}

RadioMenuElem::RadioMenuElem(RadioMenuItem::Group& gr,
                             const Glib::ustring& label,
                             const AccelKey& accel_key,
                             const CallSlot& slot)
  : gr_(&gr)
{
  CheckMenuItem* item = manage(new RadioMenuItem(*gr_, label, true));
  child_ = item;
  set_accel_key(accel_key);
  if(slot)
    item->signal_toggled().connect(slot);
  child_->show();
}

TearoffMenuElem::TearoffMenuElem(TearoffMenuItem& child)
: Element(child)
{}

TearoffMenuElem::TearoffMenuElem(const CallSlot& slot)
{
  child_ = manage(new TearoffMenuItem());
  if(slot)
    child_->signal_activate().connect(slot);
  child_->show();
}

TearoffMenuElem::TearoffMenuElem(const AccelKey& accel_key,
                                 const CallSlot& slot)
{
  child_ = manage(new TearoffMenuItem());
  set_accel_key(accel_key);
  if(slot)
    child_->signal_activate().connect(slot);
  child_->show();
}

} /* namespace Menu_Helpers */

} /* namespace Gtk */

