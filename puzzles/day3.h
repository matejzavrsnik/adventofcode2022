#pragma once

#include "../reusables/sets_intersection_plural.h"
#include "filesystem/read_write_file.h"
#include <numeric>
#include <set>
#include <algorithm>
#include <span>

long prioritise(char item)
{
   // Lowercase item types a through z have priorities 1 through 26.
   // Uppercase item types A through Z have priorities 27 through 52.
   if(item >= 'a' && item <= 'z') return item-'a'+1;
   if(item >= 'A' && item <= 'Z') return item-'A'+27;
   std::terminate();
}

// my first attempt that worked; see below for refactor
long prioritise_rearrangement(std::string input_file)
{
   auto rucksacks_content = mzlib::read_file_lines(input_file);

   long sum_priority = std::accumulate(
      rucksacks_content.begin(),
      rucksacks_content.end(),
      0,
      [](auto priority, const auto& contents){
         const auto& contents_middle = contents.begin()+contents.size()/2;
         std::set<char> first_compartment{contents.begin(), contents_middle};
         std::set<char> already_prioritised;
         std::for_each(contents_middle, contents.end(),
            [&first_compartment, &priority, &already_prioritised](const auto& item){
               if(first_compartment.contains(item) && !already_prioritised.contains(item))
               {
                  priority += prioritise(item);
                  already_prioritised.insert(item);
               }
            });
         return priority;
      });

   return sum_priority;
}

// my first attempt
long find_badges(std::string input_file)
{
   auto rucksacks_content = mzlib::read_file_lines(input_file);

   long priorities = 0;
   for(
      auto first_in_group_it = rucksacks_content.begin();
      first_in_group_it != rucksacks_content.end();
      first_in_group_it+=3)
   {
      // look, it works, ok? :)
      auto elf1 = *(first_in_group_it);
      auto elf2 = *(first_in_group_it + 1);
      auto elf3 = *(first_in_group_it + 2);
      std::sort(elf1.begin(), elf1.end());
      std::sort(elf2.begin(), elf2.end());
      std::sort(elf3.begin(), elf3.end());
      std::vector<char> possible_badges;
      std::set_intersection(
         elf1.begin(), elf1.end(),
         elf2.begin(), elf2.end(),
         std::back_inserter(possible_badges)
      );
      std::vector<char> hopefully_one_badge;
      std::set_intersection(
         possible_badges.begin(), possible_badges.end(),
         elf3.begin(), elf3.end(),
         std::back_inserter(hopefully_one_badge)
      );
      if(hopefully_one_badge.size()!=1)
         std::terminate();
      priorities += prioritise(hopefully_one_badge[0]);
   }

   return priorities;
}

namespace bonus
{

// tried to refactor a bit but ran out of time at this point
long find_badges(std::string input_file)
{
   auto rucksacks_content = mzlib::read_file_lines(input_file);

   long priorities = 0;
   for(
      auto first_in_group_it = rucksacks_content.begin();
      first_in_group_it != rucksacks_content.end();
      first_in_group_it+=3)
   {
      auto elf1 = *(first_in_group_it);
      auto elf2 = *(first_in_group_it + 1);
      auto elf3 = *(first_in_group_it + 2);
      std::sort(elf1.begin(), elf1.end());
      std::sort(elf2.begin(), elf2.end());
      std::sort(elf3.begin(), elf3.end());

      auto hopefully_one_badge = sets_intersection_plural(elf1, elf2, elf3);
      if(hopefully_one_badge.size()!=1)
         std::terminate();

      priorities += prioritise(hopefully_one_badge[0]);
   }

   return priorities;
}

// not sure why it didn't occur to me earlier that this is an operation over sets
long prioritise_rearrangement(std::string input_file)
{
   auto rucksacks_content = mzlib::read_file_lines(input_file);

   return std::accumulate(rucksacks_content.begin(), rucksacks_content.end(),0,
      [](auto priority, auto& contents)
      {
         // split in two
         const auto contents_middle = contents.length()/2;
         std::span first_compartment(&contents[0], &contents[contents_middle]);
         std::span second_compartment(&contents[contents_middle], &contents[contents.length()]);
         // sort (in place) so that set operations can work
         std::sort(first_compartment.begin(), first_compartment.end());
         std::sort(second_compartment.begin(), second_compartment.end());
         // get intersection
         std::set<char> intersection;
         std::set_intersection(
            first_compartment.begin(), first_compartment.end(),
            second_compartment.begin(), second_compartment.end(),
            std::inserter(intersection, intersection.end())
         );
         // each set intersection item is in both compartmens, as per definition
         for(auto item : intersection)
            priority += prioritise(item); // calc priority
         return priority;
      });
}

}