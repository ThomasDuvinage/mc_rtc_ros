/*
 * Copyright 2016-2020 CNRS-UM LIRMM, CNRS-AIST JRL
 */

#pragma once

#include "FormElement.h"

namespace mc_rtc_rviz
{

struct Schema;

using SchemaStore = std::map<std::string, Schema>;
using FormElements = std::vector<FormElement *>;
using FormMaker = std::function<FormElements(QWidget *, const mc_rtc::Configuration &)>;

/** A schema after having been read from the disk
 *
 * Its purpose is to provide a form creator
 *
 */
struct Schema
{
  Schema() = default;

  /** Create a tuple from a collection of schemas */
  Schema(const std::vector<Schema> & schemas);

  /** Load a schema from a file on-disk */
  Schema(const std::string & file);

  /** Load a schema from a file on disk with a specific title */
  Schema(const std::string & file, const std::string & title);

  /** Load a schema from data, source is the on-disk location of the schema */
  Schema(const mc_rtc::Configuration & data,
         const std::string & source,
         const std::string & title = "",
         bool required = false);

  /** Returns the title of the schema */
  inline const std::string & title() const { return title_; }

  /** True if the schema represents an object, false otherwise */
  inline bool is_object() const { return is_object_; }

  /** True if the schema represents a tuple, false otherwise */
  inline bool is_tuple() const { return is_tuple_; }

  /** A callback to create form elements from the schema */
  FormMaker create_form = [](QWidget *, const mc_rtc::Configuration &) -> FormElements { return {}; };

  static SchemaStore & store();

private:
  /** Recursively resolve allOf property */
  mc_rtc::Configuration resolveAllOf(const mc_rtc::Configuration & s, const std::string & source) const;

private:
  std::string title_;
  bool is_object_ = false;
  bool is_tuple_ = false;

  void init(const mc_rtc::Configuration & data, const std::string & source, const std::string & title, bool required);
};

} // namespace mc_rtc_rviz
