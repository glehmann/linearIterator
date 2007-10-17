#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "itkSimpleFilterWatcher.h"

#include "itkImageLinearConstIterator.h"

#include "itkImageLinearConstIteratorWithIndex.h"
#include "itkTimeProbe.h"
#include <iomanip>


int main(int, char * argv[])
{
  const int dim = 2;
  
  typedef unsigned char PType;
  typedef itk::Image< PType, dim > IType;

  typedef itk::ImageFileReader< IType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );

  IType::Pointer image = reader->GetOutput();
  image->Update();
  image->DisconnectPipeline();

  int tests = 500;
  itk::TimeProbe OrigTime;
  itk::TimeProbe NewTime;
  NewTime.Start();
  for (unsigned i = 0; i< tests;i++)
    {
    typedef itk::ImageLinearConstIterator<IType> IteratorType;
    IteratorType it(image, image->GetLargestPossibleRegion());
    it.SetDirection(0);
    it.GoToBegin();
    while (! it.IsAtEnd() )
      {
      while (! it.IsAtEndOfLine() )
	{
	PType value = it.Get();
	++it;
	}
      it.NextLine();
      }
    }
  NewTime.Stop();
  OrigTime.Start();
  for (unsigned i = 0; i< tests;i++)
    {
    typedef itk::ImageLinearConstIteratorWithIndex<IType> IteratorType;
    IteratorType it(image, image->GetLargestPossibleRegion());
    it.SetDirection(0);
    it.GoToBegin();
    while (! it.IsAtEnd() )
      {
      while (! it.IsAtEndOfLine() )
	{
	PType value = it.Get();
	++it;
	}
      it.NextLine();
      }
    }
  OrigTime.Stop();
//   typedef itk::ImageFileWriter< IType > WriterType;
//   WriterType::Pointer writer = WriterType::New();
//   writer->SetInput( reader->GetOutput() );
//   writer->SetFileName( argv[2] );
//   writer->Update();
  std::cout << "Iteration speed : Old \t New" << std::endl;
  std::cout << std::setprecision(3) <<  OrigTime.GetMeanTime() << "\t"
	    << NewTime.GetMeanTime() << std::endl;

  return EXIT_SUCCESS;
}

