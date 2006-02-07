<?php

  class atkMockDb extends atkDb 
  {
    var $m_type = "mock";
    var $m_results = array();
    var $m_regex_results = array();
    var $m_query_history = array();
          
    /**
     * Connect to the database.
     * @return int Connection status
     * @abstract
     */
    function connect()
    {
      return true;
    }

    /**
     * Parse and execute a query.
     *
     * If the query is a select query, the rows can be retrieved using the
     * next_record() method.
     *
     * @param String $query The SQL query to execute
     * @param int $offset Retrieve the results starting at the specified
     *                    record number. Pass -1 or 0 to start at the first
     *                    record.
     * @param int $limit Indicates how many rows to retrieve. Pass -1 to
     *                   retrieve all rows.
     * @abstract
     */
    function query($query, $offset=-1, $limit=-1)
    {
      $this->m_query_history[] = $query;
      
      if ($this->m_results[$offset][$limit][$query]) return $this->m_results[$offset][$limit][$query];
      if (!empty($this->m_regex_results))
      {
        foreach ($this->m_regex_results[$offset][$limit] as $regex => $result)
        {
          if (preg_match($regex, $query)) return $result;
        }
      }
      return true;
    }
    
    
    /**
     * Get all rows that are the result
     * of a certain specified query
     *
     * Note: This is not an efficient way to retrieve
     * records, as this will load all records into one
     * array into memory. If you retrieve a lot of records,
     * you might hit the memory_limit and your script will die.
     *
     * @param $query the query
     * @return array with rows
     */
    function getrows($query, $offset=-1, $limit=-1)
    {
      $res = $this->query($query, $offset, $limit);
      if (is_array($res))
        return $res;
      return array();
    }
    
    function setResult($result, $query, $offset=-1, $limit=-1)
    {
      $this->m_results[$offset][$limit][$query] = $result;
    }
    
    function setRegexResult($result, $regex, $offset=-1, $limit=-1)
    {
      $this->m_regex_results[$offset][$limit][$regex] = $result;
    }
  }

?>