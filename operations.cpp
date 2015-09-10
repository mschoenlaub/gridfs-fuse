/*
 *  Copyright 2009 Michael Stephens
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "operations.h"
#include "options.h"
#include "local_gridfile.h"
#include <memory>

#include <mongocxx/client.hpp>

std::map<std::string, LocalGridFile::ptr> open_files;

//! Automatically call ScopedDbConnection::done() when a shared_ptr of one is
//  about to be deleted (presumebly because it is passing out of scope).
struct SDC_deleter {
  void operator()(mongo::ScopedDbConnection* sdc) {
    sdc->done();
  }
};

std::shared_ptr<mongo::ScopedDbConnection> make_ScopedDbConnection(void) {
  mongo::ScopedDbConnection *sdc = mongo::ScopedDbConnection::getScopedDbConnection(*gridfs_options.conn_string);
  if (gridfs_options.username) {
    bool digest = true;
    std::string err = "";
    sdc->conn().DBClientWithCommands::auth(gridfs_options.db, gridfs_options.username, gridfs_options.password, err, digest);
    fprintf(stderr, "DEBUG: %s\n", err.c_str());
  }

  return std::shared_ptr<mongo::ScopedDbConnection>(sdc, SDC_deleter());
}
