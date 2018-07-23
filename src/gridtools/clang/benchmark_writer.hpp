//===--------------------------------------------------------------------------------*- C++ -*-===//
//                         _       _
//                        | |     | |
//                    __ _| |_ ___| | __ _ _ __   __ _
//                   / _` | __/ __| |/ _` | '_ \ / _` |
//                  | (_| | || (__| | (_| | | | | (_| |
//                   \__, |\__\___|_|\__,_|_| |_|\__, | - GridTools Clang DSL
//                    __/ |                       __/ |
//                   |___/                       |___/
//
//
//  This file is distributed under the MIT License (MIT).
//  See LICENSE.txt for details.
//
//===------------------------------------------------------------------------------------------===//

#ifndef GRIDTOOLS_CLANG_BENCHMARK_WRITER_HPP
#define GRIDTOOLS_CLANG_BENCHMARK_WRITER_HPP

#include "gridtools/clang/Support/External/json/json.hpp"
#include "gridtools/clang_dsl.hpp"
#include <chrono>
#include <ctime>
#include <fstream>
#include <vector>

namespace gridtools {

namespace clang {

class benchmarker {
  using json = nlohmann::json;

public:
  benchmarker(int nIter = 100) : nIter_(nIter), times_(nIter, 0) {}

  ///@brief runs the benchmaks of the given computation and wirtes the output to the specified .json
  /// file
  template <typename GTStencil>
  void runBenchmarks(GTStencil& computation, std::string filename) {

    // Gather the data
    std::string name = computation.get_name();
    for(int i = 0; i < nIter_; ++i) {
      computation.reset_meters();
      computation.run();
      auto stencils = computation.getStencils();
      for(auto stencil : stencils) {
        times_[i] += stencil->get_time();
      }
    }

    // Read the existing file
    std::ifstream fsin(filename);
    if(!fsin.is_open()) {
      std::cerr << "could not open file" << filename << std::endl;
      assert(false);
    }
    if(fsin.peek() == std::ifstream::traits_type::eof()) {
      std::cerr << "\nbenchmark-file was not initialized, call benchmarker.initOutput() for "
                << filename << "\n"
                << std::endl;
      assert(false);
    }
    json j;
    fsin >> j;
    fsin.close();

    // Emplace the new times
    json jMesurement(times_);
    json jData;
    jData["mesurements"] = jMesurement;
    jData["stencil"] = name;
    json jArray = json::array();
    jArray.push_back(jData);
    j["times"].push_back(jData);

    std::ofstream fsout(filename, std::ios::out | std::ios::trunc);
    fsout << j.dump(2) << std::endl;
    fsout.close();
  }

  ///@brief intiializes the .json file with the required meta-information that is passed in the
  /// configuartion-vector and the domain size. The configuartion vector contaions:
  /// configuartion[0] = clustername           [example: "kesch"]
  /// configuartion[1] = configuration name    [example: "kesch_gcc"]
  /// configuartion[2] = host name             [example: "keschln-0003"]
  /// configuartion[3] = backend               [example: "cuda"]
  /// configuartion[4] = compiler              [example: "/usr/bin/nvcc"]
  /// configuartion[5] = grid type             [example: "structured"]
  /// configuartion[6] = name of the run       [example: "GTClang-dycore"]
  /// configuartion[7] = precision             [example: "double"]
  /// configuartion[8] = git-tag               [example: "ba428e3c71d7b4f4ed5dadd7b142419c862cfc93"]
  /// configuartion[9] = version               [example: "0.1"]
  void initOutput(const std::vector<std::string>& configuartion, const std::vector<int>& domainsize,
                  std::string filename) const {
    assert(configuartion.size() == 10);
    // get the current time as GMT string
    std::chrono::time_point<std::chrono::system_clock> time;
    time = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(time);
    auto gmt_time = gmtime(&current_time);
    std::ostringstream oss;
    oss << std::put_time(gmt_time, "%Y-%m-%d %H:%M:%S");
    std::string timestring = oss.str();

    json jOut;
    json jConfig;
    jConfig["clustername"] = configuartion[0];
    jConfig["configname"] = configuartion[1];
    jConfig["hostname"] = configuartion[2];
    jOut["config"] = jConfig;
    jOut["datetime"] = timestring;

    json jDomain(domainsize);
    jOut["domain"] = jDomain;

    json jRuntime;
    jRuntime["backend"] = configuartion[3];
    jRuntime["compiler"] = configuartion[4];
    jRuntime["datetime"] = timestring;
    jRuntime["grid"] = configuartion[5];
    jRuntime["name"] = configuartion[6];
    jRuntime["precision"] = configuartion[7];
    jRuntime["version"] = configuartion[8];
    jOut["runtime"] = jRuntime;
    jOut["version"] = configuartion[9];

    std::ofstream fs(filename, std::ios::out | std::ios::trunc);
    if(!fs.is_open()) {
      std::cerr << "could not open file" << filename << std::endl;
      assert(false);
    }

    fs << jOut.dump(2) << std::endl;
    fs.close();
  }

private:
  int nIter_;
  std::vector<double> times_;
};
}
}

#endif // GRIDTOOLS_CLANG_BENCHMARK_WRITER_HPP
