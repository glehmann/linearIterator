#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkTimeProbe.h"
#include <iomanip>
#include "itkMultiThreader.h"


#include <itkSmoothingRecursiveGaussianImageFilter.h>
#include "itkSmoothingRecursiveGaussianImageFilterMod.h"

int main(int, char * argv[])
{
  itk::MultiThreader::SetGlobalMaximumNumberOfThreads(1);
  const int dim = 2;
  float sigma = 2.0;
  typedef unsigned char PType;
  typedef itk::Image< PType, dim > IType;

  typedef itk::ImageFileReader< IType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );

  IType::Pointer image = reader->GetOutput();
  image->Update();
  image->DisconnectPipeline();

  typedef itk::SmoothingRecursiveGaussianImageFilter<IType, IType> OrigFilterType;
  typedef itk::SmoothingRecursiveGaussianImageFilterMod<IType, IType> ModFilterType;

  OrigFilterType::Pointer filtA = OrigFilterType::New();
  ModFilterType::Pointer filtB = ModFilterType::New();

  filtA->SetSigma(sigma);
  filtA->SetInput(image);
  filtB->SetSigma(sigma);
  filtB->SetInput(image);

  itk::TimeProbe OrigTime;
  itk::TimeProbe NewTime;

  for (unsigned i = 0; i<20;i++)
    {
     filtA->Modified();
     OrigTime.Start();
     filtA->Update();
     OrigTime.Stop();

     filtB->Modified();
     NewTime.Start();
     filtB->Update();
     NewTime.Stop();

    }

  std::cout << "Finished" << std::endl;

  typedef itk::ImageFileWriter< IType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( filtA->GetOutput() );
  writer->SetFileName( argv[2] );
  writer->Update();

  writer->SetInput( filtB->GetOutput() );
  writer->SetFileName( argv[3] );
  writer->Update();
  std::cout << std::setprecision(3) <<  OrigTime.GetMeanTime() << "\t"
	    << NewTime.GetMeanTime() << std::endl;

  return EXIT_SUCCESS;
}

