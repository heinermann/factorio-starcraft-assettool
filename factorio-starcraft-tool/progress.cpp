#include "progress.h"

#include <mutex>
#include <iostream>
#include <iomanip>

ProgressBar::ProgressBar(const std::string& name, unsigned max_value, char fill_chr, unsigned width)
  : max_value(max_value)
  , width(width)
  , fill_chr(fill_chr)
  , name(name)
{}

void ProgressBar::increment_progress() {
  std::lock_guard guard(progress_mutex);
  current_value++;
}

void ProgressBar::inc_show_progress() {
  increment_progress();
  display(std::cerr);
}


void ProgressBar::display(std::ostream& ostream) {
  std::lock_guard guard(progress_mutex);
  ostream << '\r';

  char oldfill = ostream.fill();

  unsigned num_progress_chars = width - name.size() - 8;
  unsigned num_filled_chars = num_progress_chars * current_value / max_value;
  unsigned num_unfilled_chars = num_progress_chars - num_filled_chars;
  unsigned percentage = 100 * current_value / max_value;

  ostream << name << " [";
  ostream << std::setfill(fill_chr) << std::setw(num_filled_chars) << "";
  ostream << std::setfill(' ') << std::setw(num_unfilled_chars) << "";
  ostream << "] " << std::setw(3) << percentage << "%";

  ostream.flush();

  ostream.fill(oldfill);
}